#pragma once

#include "MainMenuState.h"

class Game {
private:
	Graphics graphics;
	sf::RenderWindow* window;
	sf::Event event;
	float dt;
	sf::Clock dtClock;
	std::map<std::string, int> supportedKeys;

	StateData stateData;
	std::stack<State*> states;

	// Inits
	void			initVariables();
	void			initGraphics();
	void			initWindow();
	void			initKeys();
	void			initStateData();
	void			initStates();
public:
	Game();
	virtual ~Game();

	// Updates
	void			updateSFMLEvents();

	// Core
	void			update();
	void			render();
	void			run();
};

