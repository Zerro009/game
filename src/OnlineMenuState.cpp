#include "OnlineMenuState.h"

OnlineMenuState::OnlineMenuState(StateData* stateData) : State(stateData) {
	this->initVariables();
	this->initKeybinds();
	this->initFonts();
	this->initGui();
}

OnlineMenuState::~OnlineMenuState() {
}

// Inits
void OnlineMenuState::initVariables() {
}

void OnlineMenuState::initKeybinds() {
	std::ifstream ifs("./configs/onlinemenustate_keybinds.ini");

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

void OnlineMenuState::initFonts()
{
	if (!this->font.loadFromFile("./resources/fonts/Dosis-Light.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}


void OnlineMenuState::initGui() {
	this->buttons["EXIT_STATE"] = new gui::Button(
		10.f, 10.f,
		100.f, 40.f,
		&this->font, "Back",
		sf::Color(200, 200, 200, 200), sf::Color(255, 255, 255, 255), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0),
		sf::Color::White, sf::Color::White, sf::Color::White
	);

	this->inputFields["IPv4"] = new gui::InputField(
		10.f, 100.f,
		100.f, 40.f,
		&this->font, "",
		sf::Color::Red, sf::Color::Red, sf::Color::Red,
		sf::Color::Black, sf::Color::Black, sf::Color::Black,
		sf::Color::White, sf::Color::White, sf::Color::White
	);
}

// Updates
void OnlineMenuState::updateInput(const float dt) {

}

void OnlineMenuState::updateButtons() {
	for (auto it : this->buttons) {
		it.second->update(this->mousePosWindow);
	}

	// Quit
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void OnlineMenuState::updateInputs() {
	for (auto it : this->inputFields) {
		it.second->update(this->event);
	}
}

void OnlineMenuState::updateGui() {
	this->updateButtons();
	this->updateInputs();
}

// Renders
void OnlineMenuState::renderButtons(sf::RenderTarget* target) {
	for (auto it : this->buttons) {
		it.second->render(target);
	}
}

void OnlineMenuState::renderInputs(sf::RenderTarget* target) {
	for (auto it : this->inputFields) {
		it.second->render(target);
	}
}

void OnlineMenuState::renderGui(sf::RenderTarget* target) {
	this->renderButtons(target);
	this->renderInputs(target);
}

// Core
void OnlineMenuState::update(const float dt) {
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateGui();
}

void OnlineMenuState::render(sf::RenderTarget* target) {
	if (!target) {
		target = this->window;
	}

	this->renderGui(target);
}
