#include "Entity.h"

Entity::Entity(sf::Vector2f pos) {
	this->pos = pos;

	this->initComponents();
}

Entity::~Entity() {
}

// Inits
void Entity::initComponents() {
	this->movementComponent = NULL;
}

// Components
void Entity::createMovementComponent() {
	this->movementComponent = new MovementComponent(&this->pos);
}

// Accessors
sf::Vector2f Entity::getPos() {
	return this->pos;
}

// Funcs
void Entity::move(sf::Vector2f dir) {
	if (this->movementComponent) {
		this->movementComponent->move(dir);
	}
}
