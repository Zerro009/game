#pragma once

#include "HitboxComponent.h"
#include "MovementComponent.h"

class Entity {
private:
	void			initComponents();
protected:
	sf::RectangleShape	sprite;

	sf::Vector2f		pos;

	HitboxComponent		*hitboxComponent;
	MovementComponent	*movementComponent;
public:
	Entity(sf::Vector2f pos);
	virtual ~Entity();

	// Components
	void			createHitboxComponent(float offsetX, float offsetY, float width, float height);
	void			createMovementComponent();

	// Accessors
	sf::Vector2f		getPos();
	virtual sf::FloatRect	getNextPositionBounds(const float dt);

	// Funcs		
	void			move(sf::Vector2f dir);

	// Core
	virtual void		update(const float dt) = 0;
	virtual void		render(sf::RenderTarget *target) = 0;

};
