#include "MainMenuState.h"

MainMenuState::MainMenuState(StateData* stateData) : State(stateData) {
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initGui();
}

MainMenuState::~MainMenuState() {
}

// Inits
void MainMenuState::initVariables() {
}

void MainMenuState::initKeybinds() {
	std::ifstream ifs("mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key;
		std::string value;

		while (ifs >> key >> value)
		{
			this->keybinds[key] = this->supportedKeys->at(value);
		}
	}

	ifs.close();
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}


void MainMenuState::initGui() {
	this->buttons["GAME_STATE"] = new gui::Button(
		80.f, 100.f,
		100.f, 40.f,
		&this->font, "New Game",
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["ONLINE_STATE"] = new gui::Button(
		80.f, 180.f,
		100.f, 40.f,
		&this->font, "Online",
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		80.f, 260.f,
		100.f, 40.f,
		&this->font, "Settings",
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);

	this->buttons["EXIT_STATE"] = new gui::Button(
		80.f, 340.f,
		100.f, 40.f,
		&this->font, "Exit",
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0)
	);
}

// Updates
void MainMenuState::updateInput(const float dt) {
}

void MainMenuState::updateButtons() {
	for (auto it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	if (this->buttons["ONLINE_STATE"]->isPressed())
	{
		this->states->push(new OnlineMenuState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

// Renders
void MainMenuState::renderButtons(sf::RenderTarget *target) {
	for (auto it : this->buttons) {
		it.second->render(target);
	}
}

// Core
void MainMenuState::update(const float dt) {
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target) {
	if (!target) {
		target = this->window;
	}

	this->renderButtons(target);
}