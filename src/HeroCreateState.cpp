#include "HeroCreateState.h"

HeroCreateState::HeroCreateState(StateData *stateData) : State(stateData) {
}

HeroCreateState::~HeroCreateState() {
}

// Updates
void HeroCreateState::updateInput(const float dt) {
}

// Core
void HeroCreateState::update(const float dt) {
}

void HeroCreateState::render(sf::RenderTarget *target) {
	target->clear(sf::Color::Yellow);
}
