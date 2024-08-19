#include "Enemy.h"

Enemy::Enemy(sf::Vector2f pos, Entity *entity) : Entity(pos) {
	this->entity = entity;

	this->sprite.setSize(sf::Vector2f(20.f, 20.f));
	this->sprite.setPosition(this->pos);
	this->sprite.setFillColor(sf::Color::Red);

	this->initComponents();
}

Enemy::~Enemy() {
}

// Inits
void Enemy::initComponents() {
	this->createMovementComponent(16.f);
	this->createHitboxComponent(0.f, 0.f, 20.f, 20.f);
	this->aiComponent = new AIFollow(this, this->entity);
}

// Updates
void Enemy::updateComponents(const float dt) {
	this->aiComponent->update(dt);
	this->movementComponent->update(dt);
	this->hitboxComponent->update();
}

void Enemy::updateSprite() {
	this->sprite.setPosition(this->pos);
}

// Core
void Enemy::update(const float dt) {
	this->updateComponents(dt);
	this->updateSprite();
}

void Enemy::render(sf::RenderTarget *target) {
	target->draw(this->sprite);
	this->hitboxComponent->render(target);
}
