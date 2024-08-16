#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Vector2f *pos) {
	this->pos = pos;

	this->velocity = sf::Vector2f(0.f, 0.f);
	this->maxVelocity = 50.f;
}

MovementComponent::~MovementComponent() {
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
	this->velocity.x = this->maxVelocity * dir.x;
	this->velocity.y = this->maxVelocity * dir.y;
}

// Core
void MovementComponent::update(const float dt) {
	*this->pos += this->velocity * dt;
	this->velocity.x = 0;
	this->velocity.y = 0;
}
