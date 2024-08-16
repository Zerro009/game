#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	// Inits
	void		initComponents();
public:
	Player(sf::Vector2f pos);
	virtual ~Player();

	// Updates
	void		updateComponents(const float dt);
	void		updateSprite();

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target);
};
