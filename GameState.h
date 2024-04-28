#pragma once

#include "State.h"

class GameState : public State {
private:
	sf::View	view;
	
	// Inits
	void		initView();
	void		initKeybinds();
	void		initKeytime();

public:
	GameState(StateData *stateData);
	virtual ~GameState();

	// Updates
	void		updateView(const float dt);
	void		updateInput(const float dt);
	void		updatePlayerInput(const float dt);

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target = NULL);
};

