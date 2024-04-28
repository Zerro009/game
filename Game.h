#pragma once

#include "Graphics.h"

class Game {
private:
	Graphics graphics;
	sf::RenderWindow* window;
	sf::Event event;
	float dt;
	sf::Clock dtClock;
	std::map<std::string, int> supportedKeys;

	// Inits
	void			initVariables();
	void			initGraphics();
	void			initWindow();
	void			initKeys();
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

