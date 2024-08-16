#include "GameState.h"

GameState::GameState(StateData* stateData) : State(stateData) {
	this->initVariables();
	this->initView();
	this->initKeybinds();
	this->initKeytime();
	this->initPlayer();
}

GameState::~GameState() {
	if (this->server) {
		delete this->server;
	}
	if (this->client) {
		delete this->client;
	}
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

// Client-server
void GameState::createClient() {
	this->client = new network::Client(&this->players, "127.0.0.1");
	this->online_state = ONLINE;
}

void GameState::createServer() {
	this->server = new network::Server(&this->players);
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
	this->player->update(dt);

	this->updateClient();
	this->updateServer();

	for (auto it: this->players) {
		it->update(dt);
	}
}

void GameState::render(sf::RenderTarget* target) {
	target->clear(sf::Color::Green);
	this->player->render(target);

	for (auto it: this->players) {
		it->render(target);
	}
}
