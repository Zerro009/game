#include "GameState.h"

GameState::GameState(StateData* stateData) : State(stateData) {
	this->initVariables();
	this->initView();
	this->initKeybinds();
	this->initKeytime();
	this->initPlayer();
	this->initCamera();
	this->initLevel();
}

GameState::~GameState() {
	if (this->server) {
		delete this->server;
	}
	if (this->client) {
		delete this->client;
	}
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
	this->player = new Player(sf::Vector2f(0.f, 0.f));
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

void GameState::initLevel() {
	this->level = new Level("./levels/arena.ini");
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
		this->endState();
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
	if (!this->level->isAccessible(this->player->getNextPositionBounds(dt))) {
		if (this->player->getVelocity().x != 0.f) {
			this->player->stopVelocityX();
		}
		if (this->player->getVelocity().y != 0.f) {
			this->player->stopVelocityY();
		}
	}
	this->player->update(dt);
}

void GameState::updateCamera() {
	this->camera.setCenter(
		this->player->getPos()
	);
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

	this->updateClient();
	this->updateServer();
}

void GameState::render(sf::RenderTarget* target) {
	this->window->setView(this->camera);

	this->level->render(target);
	this->player->render(target);
}
