#pragma once

#include "pch.h"

class HitboxComponent {
private:
	sf::Vector2f		*pos;
	sf::RectangleShape	hitbox;
	sf::FloatRect		next;

	float			offsetX;
	float			offsetY;
public:
	HitboxComponent(sf::Vector2f *pos, float offsetX, float offsetY, float width, float height);
	virtual ~HitboxComponent();

	// Accessors
	sf::Vector2f		getPosition();
	sf::FloatRect		getGlobalBounds();
	sf::FloatRect		getNextPosition(sf::Vector2f velocity);

	// Modifiers
	
	// Funcs
	bool			intersects(const sf::FloatRect frect);

	// Core
	void			update();
	void			render(sf::RenderTarget *target);
};
