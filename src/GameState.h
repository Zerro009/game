#pragma once

#include "State.h"
#include "Player.h"
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
	std::vector<Player *>	players;

	network::Client	*client;
	network::Server	*server;
	short unsigned	online_state;

	
	// Inits
	void		initVariables();
	void		initView();
	void		initKeybinds();
	void		initKeytime();
	void		initPlayer();

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
	void		updateClient();
	void		updateServer();

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target = NULL);
};

