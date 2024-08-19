#pragma once

#include "AttributeComponent.h"
#include "HitboxComponent.h"
#include "MovementComponent.h"
#include "AIFollow.h"

class Entity {
private:
	void			initComponents();
protected:
	sf::RectangleShape	sprite;

	sf::Vector2f		pos;

	AttributeComponent	*attributeComponent;
	HitboxComponent		*hitboxComponent;
	MovementComponent	*movementComponent;
	AIComponent		*aiComponent;
public:
	Entity(sf::Vector2f pos);
	virtual ~Entity();

	// Components
	void			createAttributeComponent();
	void			createHitboxComponent(float offsetX, float offsetY, float width, float height);
	void			createMovementComponent(float maxVelocity);

	AIComponent		*getAiComponent();

	// Accessors
	unsigned char		getLevel();
	unsigned int		getHp();
	unsigned int		getHpMax();

	sf::Vector2f		getPos();
	virtual sf::FloatRect	getNextPositionBounds(const float dt);

	// Modifiers
	void			stopVelocity();
	void			stopVelocityX();
	void			stopVelocityY();

	// Funcs		
	void			move(sf::Vector2f dir);

	// Core
	virtual void		update(const float dt) = 0;
	virtual void		render(sf::RenderTarget *target) = 0;

};
