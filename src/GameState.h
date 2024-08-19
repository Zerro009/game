#pragma once

#include "State.h"
#include "Player.h"
#include "Enemy.h"
#include "Level.h"
#include "network.h"
#include "gui.h"

enum online_state {
	OFFLINE,
	HOST,
	ONLINE,	
};

class GameState : public State {
private:
	sf::View		view;
	Player			*player;
	Enemy			*enemy;
	Level			*level;

	network::Client		*client;
	network::Server		*server;
	short unsigned		online_state;

	sf::View		camera;
	
	gui::ProgressBar	*hpBar;

	// Inits
	void		initVariables();
	void		initView();
	void		initKeybinds();
	void		initKeytime();
	void		initPlayer();
	void		initCamera();
	void		initLevel();
	void		initEnemies();
	void		initGui();

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
	void		updateEnemiesAi();
	void		updateEnemies(const float dt);
	void		updateGui();
	void		updateClient();
	void		updateServer();

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target = NULL);
};

