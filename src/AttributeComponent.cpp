#include "AttributeComponent.h"

AttributeComponent::AttributeComponent() {
	this->level = 1;
	this->exp = 0;

	this->strength = 1;
	this->agility = 1;
	this->intelligence = 1;

	this->hpMax = 100;
	this->hp = 100;
}

AttributeComponent::~AttributeComponent() {
}

// Accessors
unsigned char AttributeComponent::getLevel() {
	return this->level;
}

unsigned int AttributeComponent::getHp() {
	return this->hp;
}

unsigned int AttributeComponent::getHpMax() {
	return this->hpMax;
}

// Core
void AttributeComponent::update() {
}
