#include "Entity.h"

Entity::Entity(sf::Vector2f pos) {
	this->pos = pos;

	this->initComponents();
}

Entity::~Entity() {
	delete this->movementComponent;
	delete this->hitboxComponent;
}

// Inits
void Entity::initComponents() {
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
}

// Components
void Entity::createHitboxComponent(float offsetX, float offsetY, float width, float height) {
	this->hitboxComponent = new HitboxComponent(&this->pos, offsetX, offsetY, width, height);
}

void Entity::createMovementComponent() {
	this->movementComponent = new MovementComponent(&this->pos);
}

// Accessors
sf::Vector2f Entity::getPos() {
	return this->pos;
}

sf::FloatRect Entity::getNextPositionBounds(const float dt) {
	if (this->hitboxComponent && this->movementComponent) {
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// Funcs
void Entity::move(sf::Vector2f dir) {
	if (this->movementComponent) {
		this->movementComponent->move(dir);
	}
}
