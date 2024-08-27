#include "Player.h"

Player::Player(sf::Vector2f pos, sf::Texture *texture) : Entity(pos) {
	this->sprite.setPosition(this->pos);

	this->createAttributeComponent();
	this->createMovementComponent(64.f);
	this->createHitboxComponent(0.f, 0.f, 32.f, 32.f);
	this->createAnimationComponent(texture);

	this->initAnimations();
}

Player::~Player() {
}

// Inits
void Player::initAnimations() {
	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 1, 0, 32, 32);
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
void Player::updateAnimation(const float dt) {
	if (this->movementComponent->getState(IDLE)) {
		this->animationComponent->play("IDLE", dt);
	}
}

void Player::updateComponents(const float dt) {
	this->movementComponent->update(dt);
	this->updateAnimation(dt);
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
