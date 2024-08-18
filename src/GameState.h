#pragma once

#include "State.h"
#include "Player.h"
#include "Level.h"
#include "network.h"

enum online_state {
	OFFLINE,
	HOST,
	ONLINE,	
};

class GameState : public State {
private:
	sf::View		view;
	Player			*player;
	Level			*level;

	network::Client	*client;
	network::Server	*server;
	short unsigned	online_state;

	sf::View	camera;
	
	// Inits
	void		initVariables();
	void		initView();
	void		initKeybinds();
	void		initKeytime();
	void		initPlayer();
	void		initCamera();
	void		initLevel();

	// Client-server
	void		createClient();
	void		createServer();

public:
	GameState(StateData *stateData);
	virtual ~GameState();

	// Updates
	void		updateView(const float dt);
	void		updateInput(const float dt);
	void		updatePlayerInput(const float dt);
	void		updatePlayer(const float dt);
	void		updateCamera();
	void		updateClient();
	void		updateServer();

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target = NULL);
};

