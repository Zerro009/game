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
	this->createAttributeComponent();
	this->createMovementComponent(64.f);
	this->createHitboxComponent(0.f, 0.f, 20.f, 20.f);
}

// Accessors
sf::Vector2f Player::getVelocity() {
	return this->movementComponent->getVelocity();
}

// Modifiers
void Player::stopVelocity() {
	this->movementComponent->stopVelocity();
}

void Player::stopVelocityX() {
	this->movementComponent->stopVelocityX();
}

void Player::stopVelocityY() {
	this->movementComponent->stopVelocityY();
}

// Updates
void Player::updateComponents(const float dt) {
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
}

void Player::updateSprite() {
	this->sprite.setPosition(pos);
}

// Core
void Player::update(const float dt) {
	this->updateComponents(dt);
	this->updateSprite();
}

void Player::render(sf::RenderTarget *target) {
	target->draw(this->sprite);
	this->hitboxComponent->render(target);
}
