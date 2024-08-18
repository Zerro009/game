#include "Level.h"

Level::Level(std::string path) {
	std::ifstream ifs(path);

	if (ifs.is_open()) {
		int width, height;
		ifs >> this->width;
		ifs >> this->height;

		int code;
		std::string texture;
		while (ifs >> code >> texture) {
			this->tiles.push_back(
				new Tile(texture)
			);
		}
	}

	ifs.close();
}

Level::~Level() {
}

// Inits
// Funcs
bool Level::isAccessible(sf::FloatRect next) {
	if (next.left < 0 || next.left + next.width > this->width * TILE_SIZE) {
		return false;
	}
	if (next.top < 0 || next.top + next.height > this->height * TILE_SIZE) {
		return false;
	}
	return true;
}

// Core
void Level::update(const float dt) {
}

void Level::render(sf::RenderTarget *target) {
	for (int row = 0; row < this->height; row++) {
		for (int col = 0; col < this->width; col++) {
			int x = TILE_SIZE * col;
			int y = TILE_SIZE * row;
			this->tiles[0]->setPosition(
				sf::Vector2f(
					x,
					y
				)
			);
			this->tiles[0]->render(target);
		}
	}
}
