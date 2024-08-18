#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	// Inits
	void		initComponents();
public:
	Player(sf::Vector2f pos);
	virtual ~Player();

	// Accessors
	sf::Vector2f	getVelocity();

	// Modifiers
	void		stopVelocity();
	void		stopVelocityX();
	void		stopVelocityY();

	// Updates
	void		updateComponents(const float dt);
	void		updateSprite();

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target);
};
