#pragma once

#include "Graphics.h"

class State;

class StateData {
public:
	StateData() {};

	sf::RenderWindow* window;
	Graphics* graphics;
	std::map<std::string, int>* supportedKeys;
	std::stack<State *>* states;
};

class State {
protected:
	StateData* stateData;
	std::stack<State*>* states;
	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keytime;
	float keytimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

public:
	State(StateData *stateData);
	virtual ~State();

	// Accessors
	const bool			getQuit() const;
	const bool			getKeytime();

	// Funcs
	void				endState();
	void				pauseState();
	void				unpauseState();

	// Updates
	virtual void		updateMousePositions(sf::View* view = NULL);
	virtual	void		updateKeytime(const float dt);
	virtual void		updateInput(const float dt) = 0;

	// Core
	virtual void		update(const float dt) = 0;
	virtual void		render(sf::RenderTarget *target = NULL) = 0;
};

