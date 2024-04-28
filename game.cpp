#include "Game.h"

Game::Game() {
	this->initVariables();
	this->initGraphics();
	this->initWindow();
	this->initKeys();
}

Game::~Game() {
}

// Inits
void Game::initVariables() {
	this->window = nullptr;
	this->dt = 0.f;
}

void Game::initGraphics() {
	this->graphics.loadFromFile("graphics.ini");
}

void Game::initWindow() {
	if (this->graphics.fullscreen)
		this->window = new sf::RenderWindow(
			this->graphics.resolution,
			this->graphics.title,
			sf::Style::Fullscreen,
			this->graphics.contextSettings);
	else
		this->window = new sf::RenderWindow(
			this->graphics.resolution,
			this->graphics.title,
			sf::Style::Titlebar | sf::Style::Close,
			this->graphics.contextSettings);

	this->window->setFramerateLimit(this->graphics.framerateLimit);
	this->window->setVerticalSyncEnabled(this->graphics.vSync);
}

void Game::initKeys() {
	std::ifstream ifs("supported_keys.ini");

	if (ifs.is_open()) {
		std::string key;
		int value;

		while (ifs >> key >> value) {
			this->supportedKeys[key] = value;
		}
	}

	ifs.close();
}

// Updates
void Game::updateSFMLEvents() {
	while (this->window->pollEvent(this->event)) {
		if (this->event.type == sf::Event::Closed) {
			this->window->close();
		}
	}
}

// Core
void Game::update() {
	this->dt = this->dtClock.restart().asSeconds();
	this->updateSFMLEvents();
}

void Game::render() {
	this->window->clear();

	this->window->display();
}

void Game::run() {
	while (this->window->isOpen()) {
		this->update();
		this->render();
	}
}