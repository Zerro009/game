#pragma once

#include "Player.h"
#include "State.h"
#include "gui.h"

class HeroCreateState : public State {
private:
	// Inits
public:
	HeroCreateState(StateData *stateData);
	virtual ~HeroCreateState();

	// Updates
	void			updateInput(const float dt);

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target);
};
