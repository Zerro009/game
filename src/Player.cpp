#include "Player.h"

Player::Player(sf::Vector2f pos) : Entity(pos) {
	this->sprite.setSize(sf::Vector2f(20.f, 20.f));
	this->sprite.setPosition(this->pos);
	this->sprite.setFillColor(sf::Color::Black);

	this->initComponents();
}

Player::~Player() {
}

// Inits
void Player::initComponents() {
	this->createMovementComponent();
}

// Updates
void Player::updateComponents(const float dt) {
	this->movementComponent->update(dt);
}

void Player::updateSprite() {
	int x = this->pos.x * 0.8;
	int y = (this->pos.y + (this->pos.x / 2)) * 0.8;
	this->sprite.setPosition(sf::Vector2f(x, y));
}

// Core
void Player::update(const float dt) {
	this->updateComponents(dt);
	this->updateSprite();
}

void Player::render(sf::RenderTarget *target) {
	target->draw(this->sprite);
}
