#include "GameState.h"

GameState::GameState(StateData* stateData) : State(stateData) {
	this->initVariables();
	this->initView();
	this->initKeybinds();
	this->initKeytime();
	this->initPlayer();
	this->initCamera();
	this->initLevel();
	this->initEnemies();
	this->initGui();
}

GameState::~GameState() {
	if (this->server) {
		delete this->server;
	}
	if (this->client) {
		delete this->client;
	}
	delete this->pmenu;
	delete this->hpBar;
	delete this->enemy;
	delete this->level;
	delete this->player;
}

// Inits
void GameState::initVariables() {
	this->server = NULL;
	this->client = NULL;
	this->online_state = OFFLINE;
}

void GameState::initView() {
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->graphics->resolution.width / 2),
			static_cast<float>(this->stateData->graphics->resolution.height / 2)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->graphics->resolution.width) / 2.f,
			static_cast<float>(this->stateData->graphics->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds() {
	std::ifstream ifs("./configs/gamestate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void GameState::initKeytime() {
}

void GameState::initPlayer() {
	if (!this->playerTexture.loadFromFile("./resources/textures/man.png")) {
		std::cerr << "Can't load player texture!" << std::endl ;
	}
	this->player = new Player(sf::Vector2f(32.f, 32.f), &this->playerTexture);
}

void GameState::initCamera() {
	sf::Vector2f center = this->player->getPos();
	sf::Vector2f size = sf::Vector2f(
		this->stateData->graphics->resolution.width,
		this->stateData->graphics->resolution.height
	);

	this->camera = sf::View(
		center,
		size
	);
}

void GameState::initEnemies() {
	this->enemy = new Enemy(sf::Vector2f(96.f, 96.f), this->player);
}

void GameState::initLevel() {
	this->level = new Level("./levels/arena.ini");
}

void GameState::initGui() {
	this->hpBar = new gui::ProgressBar(
		20.f, 20.f, 100.f, 20.f,
		this->player->getHp(),
		this->player->getHpMax(),
		"HP",
		sf::Color::White,
		sf::Color::Red,
		sf::Color::Black
	);

	sf::Font f;
	this->pmenu = new Menu(&this->stateData->graphics->resolution, &f);
}

// Client-server
void GameState::createClient() {
	this->client = new network::Client("127.0.0.1");
	this->online_state = ONLINE;
}

void GameState::createServer() {
	this->server = new network::Server();
	this->online_state = HOST;
}

// Updates
void GameState::updateView(const float dt) {
}

void GameState::updateInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE")))) {
		if (!this->paused) {
			this->pauseState();
		} else {
			this->unpauseState();
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("HOST"))) && this->online_state == OFFLINE) {
		this->createServer();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CONNECT"))) && this->online_state == OFFLINE) {
		this->createClient();
	}
}

void GameState::updatePlayerInput(const float dt) {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP")))) {
		this->player->move(sf::Vector2f(0.f, -1.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN")))) {
		this->player->move(sf::Vector2f(0.f, 1.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT")))) {
		this->player->move(sf::Vector2f(1.f, 0.f));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT")))) {
		this->player->move(sf::Vector2f(-1.f, 0.f));
	}
}

void GameState::updatePlayer(const float dt) {
	// Collision with enemy
	if (this->player->getNextPositionBounds(dt).intersects(this->enemy->getNextPositionBounds(dt))) {
		this->player->stopVelocity();
	}

	// Collision with level unaccessible places
	if (!this->level->isAccessible(this->player->getNextPositionBounds(dt))) {
		this->player->stopVelocity();
	}
	this->player->update(dt);
}

void GameState::updateCamera() {
	this->camera.setCenter(
		this->player->getPos()
	);
}

void GameState::updateEnemiesAi() {
	this->enemy->getAiComponent()->execute();
}

void GameState::updateEnemies(const float dt) {
	if (this->enemy->getNextPositionBounds(dt).intersects(this->player->getNextPositionBounds(dt))) {
		this->enemy->stopVelocity();
	}

	this->enemy->update(dt);
}

void GameState::updateGui() {
	this->hpBar->update();
	this->pmenu->update(this->mousePosWindow);
}

void GameState::updateClient() {
	if (this->client) {
		this->client->listen();
		this->client->send(this->player->getPos());
	}
}

void GameState::updateServer() {
	if (this->server) {
		this->server->listen();
	}
}

// Core
void GameState::update(const float dt) {
	this->updateMousePositions(&this->view);
	this->updateInput(dt);
	this->updatePlayerInput(dt);
	this->updatePlayer(dt);
	this->updateCamera();
	this->level->update(dt);

	this->updateEnemiesAi();
	this->updateEnemies(dt);

	this->updateGui();

	this->updateClient();
	this->updateServer();
}

void GameState::render(sf::RenderTarget* target) {
	this->window->setView(this->camera);

	this->level->render(target);
	this->player->render(target);
	this->enemy->render(target);

	// GUI part
	this->window->setView(this->window->getDefaultView());

	this->hpBar->render(target);

	if (this->paused) {
		this->pmenu->render(target);
	}
}
