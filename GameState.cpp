#include "GameState.h"

GameState::GameState(StateData* stateData) : State(stateData) {
	this->initView();
	this->initKeybinds();
}

GameState::~GameState() {
}

// Inits
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
	std::ifstream ifs("gamestate_keybinds.ini");

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

// Updates
void GameState::updateView(const float dt) {
}

void GameState::updateInput(const float dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		this->endState();
	}
}

void GameState::updatePlayerInput(const float dt) {
}

// Core
void GameState::update(const float dt) {
	this->updateMousePositions(&this->view);
	this->updateInput(dt);
	this->updatePlayerInput(dt);
}

void GameState::render(sf::RenderTarget* target) {
	target->clear(sf::Color::Red);
}