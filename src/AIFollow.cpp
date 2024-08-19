#include "AIFollow.h"

AIFollow::AIFollow(Entity *self, Entity *entity) : AIComponent(self, entity) {
}

AIFollow::~AIFollow() {
}

// Core
void AIFollow::execute() {
	if (this->entity->getPos().y < this->self->getPos().y) {
		this->self->move(sf::Vector2f(0.f, -1.f));
	} else if (this->entity->getPos().y > this->self->getPos().y) {
		this->self->move(sf::Vector2f(0.f, 1.f));
	}
	if (this->entity->getPos().x < this->self->getPos().x) {
		this->self->move(sf::Vector2f(-1.f, 0.f));
	} else if (this->entity->getPos().x > this->self->getPos().x) {
		this->self->move(sf::Vector2f(1.f, 0.f));
	}
}

void AIFollow::update(const float dt) {
}
