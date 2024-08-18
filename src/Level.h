#pragma once

#include "Tile.h"

class Level {
private:
	int			width;
	int			height;
	std::vector<Tile *>	tiles;

	// Inits
public:
	Level(std::string path);
	virtual ~Level();

	// Funcs
	bool			isAccessible(sf::FloatRect next);

	// Core
	void			update(const float dt);
	void			render(sf::RenderTarget *target);
};
