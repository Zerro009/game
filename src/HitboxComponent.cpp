#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Vector2f *pos, float offsetX, float offsetY, float width, float height) {
	this->pos = pos;

	this->offsetX = offsetX;
	this->offsetY = offsetY;

	this->next.left = 0.f;
	this->next.top = 0.f;
	this->next.width = width;
	this->next.height = height;

	this->hitbox.setPosition(
		this->pos->x + offsetX,
		this->pos->y + offsetY
	);
	this->hitbox.setSize(
		sf::Vector2f(
			width,
			height
		)		
	);
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(-1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent() {
}

// Accessors
sf::Vector2f HitboxComponent::getPosition() {
	return this->hitbox.getPosition();
}

sf::FloatRect HitboxComponent::getGlobalBounds() {
	return this->hitbox.getGlobalBounds();
}

sf::FloatRect HitboxComponent::getNextPosition(sf::Vector2f velocity) {
	this->next.left = this->hitbox.getPosition().x + velocity.x;
	this->next.top = this->hitbox.getPosition().y + velocity.y;

	return this->next;
}

// Funcs
bool HitboxComponent::intersects(const sf::FloatRect frect) {
	return this->hitbox.getGlobalBounds().intersects(frect);
}

// Core
void HitboxComponent::update() {
	this->hitbox.setPosition(
		this->pos->x + this->offsetX,
		this->pos->y + this->offsetY
	);
}

void HitboxComponent::render(sf::RenderTarget *target) {
	target->draw(this->hitbox);
}
