#include "Tile.h"

Tile::Tile(std::string texture) {
	this->initSprite();
	this->initTexture(texture);
}

Tile::~Tile() {
}

// Inits
void Tile::initSprite() {
}

void Tile::initTexture(std::string texture) {
	if (!this->texture.loadFromFile(texture, sf::IntRect(0.f, 0.f, TILE_SIZE, TILE_SIZE))) {
		std::cerr << "Can't load texture: <" << texture << ">!" << std::endl; 
	} else {
		this->sprite.setTexture(this->texture);
	}
}

// Funcs
void Tile::setPosition(sf::Vector2f pos) {
	this->sprite.setPosition(pos);
}

// Core
void Tile::update(const float dt) {
}

void Tile::render(sf::RenderTarget *target) {
	target->draw(this->sprite);
}
