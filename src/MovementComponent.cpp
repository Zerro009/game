#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Vector2f *pos, float maxVelocity) {
	this->pos = pos;

	this->velocity = sf::Vector2f(0.f, 0.f);
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent() {
}

// Accessors
sf::Vector2f MovementComponent::getVelocity() {
	return this->velocity;
}

// Modifiers
void MovementComponent::stopVelocity() {
	this->velocity = sf::Vector2f(0.f, 0.f);
}

void MovementComponent::stopVelocityX() {
	this->velocity.x = 0.f;
}

void MovementComponent::stopVelocityY() {
	this->velocity.y = 0.f;
}

// Funcs
const bool MovementComponent::getState(const short unsigned state) const {
	switch (state) {
		case IDLE:
			if (this->velocity.x == 0 && this->velocity.y == 0.f) {
				return true;
			}
			return false;
		case MOVING:
			if (this->velocity.x != 0 || this->velocity.y != 0.f) {
				return true;
			}
			return false;
		default:
			return false;
	}
}

void MovementComponent::move(sf::Vector2f dir) {
	float vector_length = sqrt(dir.x * dir.x + dir.y * dir.y);

	this->velocity.x += this->maxVelocity * (dir.x / vector_length);
	this->velocity.y += this->maxVelocity * (dir.y / vector_length);
}

// Core
void MovementComponent::update(const float dt) {
	if (this->velocity.x >= this->maxVelocity) {
		this->velocity.x = this->maxVelocity;
	}
	if (this->velocity.x <= -this->maxVelocity) {
		this->velocity.x = -this->maxVelocity;
	}
	if (this->velocity.y >= this->maxVelocity) {
		this->velocity.y = this->maxVelocity;
	}
	if (this->velocity.y <= -this->maxVelocity) {
		this->velocity.y = -this->maxVelocity;
	}
	*this->pos += this->velocity * dt;
	this->velocity.x = 0;
	this->velocity.y = 0;
}
