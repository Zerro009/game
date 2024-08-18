#pragma once

#include "pch.h"

#define TILE_SIZE 32

class Tile {
private:
	sf::Sprite		sprite;
	sf::Texture		texture;

	// Inits
	void			initSprite();
	void			initTexture(std::string texture);
public:
	Tile(std::string texture);
	virtual ~Tile();

	// Funcs
	void			setPosition(sf::Vector2f pos);

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target);
};
