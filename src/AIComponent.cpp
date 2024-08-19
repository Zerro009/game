#include "AIComponent.h"

AIComponent::AIComponent(Entity *self, Entity *entity) {
	this->self = self;
	this->entity = entity;
}

AIComponent::~AIComponent() {
}
