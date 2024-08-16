#pragma once

#include "MovementComponent.h"

class Entity {
private:
	void			initComponents();
protected:
	sf::RectangleShape	sprite;

	sf::Vector2f		pos;

	MovementComponent	*movementComponent;
public:
	Entity(sf::Vector2f pos);
	virtual ~Entity();

	// Components
	void			createMovementComponent();

	// Accessors
	sf::Vector2f		getPos();

	// Funcs		
	void			move(sf::Vector2f dir);

	// Core
	virtual void		update(const float dt) = 0;
	virtual void		render(sf::RenderTarget *target) = 0;

};
