#include "State.h"

State::State(StateData* stateData) {
	this->stateData = stateData;
	this->event = stateData->event;
	this->window = stateData->window;
	this->supportedKeys = stateData->supportedKeys;
	this->states = stateData->states;
	this->quit = false;
	this->paused = false;
	this->keytime = 0.f;
	this->keytimeMax = 10.f;
}

State::~State() {

}

// Accessors
const bool State::getQuit() const {
	return this->quit;
}

const bool State::getKeytime() {
	if (this->keytime >= this->keytimeMax)
	{
		this->keytime = 0.f;
		return true;
	}

	return false;
}

//Functions
void State::endState() {
	this->quit = true;
}

void State::pauseState() {
	this->paused = true;
}

void State::unpauseState() {
	this->paused = false;
}

// Updates
void State::updateMousePositions(sf::View* view) {
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view)
		this->window->setView(*view);

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->window->setView(this->window->getDefaultView());
}

void State::updateKeytime(const float dt) {
	if (this->keytime < this->keytimeMax) {
		this->keytime += 100.f * dt;
	}
}