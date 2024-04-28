#include "Game.h"

Game::Game() {
	this->initVariables();
	this->initGraphics();
	this->initWindow();
	this->initKeys();
	this->initStateData();
	this->initStates();
}

Game::~Game() {
	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
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

void Game::initStateData() {
	this->stateData.window = this->window;
	this->stateData.graphics = &this->graphics;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
}

void Game::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
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

	if (!this->states.empty()) {
		this->states.top()->update(this->dt);
	}
}

void Game::render() {
	this->window->clear();

	if (!this->states.empty())
		this->states.top()->render(this->window);

	this->window->display();
}

void Game::run() {
	while (this->window->isOpen() && !this->states.empty()) {
		this->update();
		this->render();
	}
}