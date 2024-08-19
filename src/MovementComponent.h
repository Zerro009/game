#pragma once

#include "pch.h"

enum movement_states {
	IDLE,
	MOVING,
};

class MovementComponent {
private:
	sf::Vector2f		*pos;

	sf::Vector2f		velocity;
	float			maxVelocity;
public:
	MovementComponent(sf::Vector2f *pos, float maxVelocity);
	virtual ~MovementComponent();

	// Accessors
	sf::Vector2f		getVelocity();

	// Modifiers
	void			stopVelocity();
	void			stopVelocityX();
	void			stopVelocityY();

	// Funcs
	const bool		getState(const short unsigned state) const;
	void			move(sf::Vector2f dir);

	// Core
	void			update(const float dt);	
};
