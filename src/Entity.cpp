#include "Entity.h"

Entity::Entity(sf::Vector2f pos) {
	this->pos = pos;

	this->initComponents();
}

Entity::~Entity() {
	delete this->aiComponent;
	delete this->movementComponent;
	delete this->hitboxComponent;
	delete this->attributeComponent;
}

// Inits
void Entity::initComponents() {
	this->attributeComponent = NULL;
	this->hitboxComponent = NULL;
	this->movementComponent = NULL;
	this->aiComponent = NULL;
}

// Components
void Entity::createAttributeComponent() {
	this->attributeComponent = new AttributeComponent();
}

void Entity::createHitboxComponent(float offsetX, float offsetY, float width, float height) {
	this->hitboxComponent = new HitboxComponent(&this->pos, offsetX, offsetY, width, height);
}

void Entity::createMovementComponent(float maxVelocity) {
	this->movementComponent = new MovementComponent(&this->pos, maxVelocity);
}

AIComponent* Entity::getAiComponent() {
	return this->aiComponent;
}

// Accessors
unsigned char Entity::getLevel() {
	if (this->attributeComponent) {
		return this->attributeComponent->getLevel();
	}
	return 0;
}

unsigned int Entity::getHp() {
	if (this->attributeComponent) {
		return this->attributeComponent->getHp();
	}
	return 0;
}

unsigned int Entity::getHpMax() {
	if (this->attributeComponent) {
		return this->attributeComponent->getHpMax();
	}
	return 0;
}

sf::Vector2f Entity::getPos() {
	return this->pos;
}

sf::FloatRect Entity::getNextPositionBounds(const float dt) {
	if (this->hitboxComponent && this->movementComponent) {
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}
	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

// Modifiers
void Entity::stopVelocity() {
	this->movementComponent->stopVelocity();
}

void Entity::stopVelocityX() {
	this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY() {
	this->movementComponent->stopVelocityY();
}

// Funcs
void Entity::move(sf::Vector2f dir) {
	if (this->movementComponent) {
		this->movementComponent->move(dir);
	}
}
