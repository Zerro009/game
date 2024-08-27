#pragma once

#include "Entity.h"

class Player : public Entity {
private:
	// Inits
	void		initAnimations();
public:
	Player(sf::Vector2f pos, sf::Texture *texture);
	virtual ~Player();

	// Accessors
	sf::Vector2f	getVelocity();

	// Modifiers
	void		stopVelocity();
	void		stopVelocityX();
	void		stopVelocityY();

	// Updates
	void		updateAnimation(const float dt);
	void		updateComponents(const float dt);
	void		updateSprite();

	// Funcs

	// Updates

	// Core
	void		update(const float dt);
	void		render(sf::RenderTarget *target);
};
