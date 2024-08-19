#pragma once

#include "Entity.h"

class Enemy : public Entity {
private:
	Entity			*entity;

	// Inits
	void			initComponents();
public:
	Enemy(sf::Vector2f pos, Entity *entity);
	virtual ~Enemy();

	// Updates
	void			updateComponents(const float dt);
	void			updateSprite();

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target);
};
