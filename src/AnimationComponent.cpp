#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite *sprite, sf::Texture *texture)
	: sprite(sprite), texture(texture), lastAnimation(NULL), priorityAnimation(NULL) {
}

AnimationComponent::~AnimationComponent() {
	for (auto it : this->animations) {
		delete it.second;
	}
}

// Accessors
const bool AnimationComponent::isDone(const std::string key) {
	return this->animations[key]->isDone();
}

// Funcs
void AnimationComponent::addAnimation(
	const std::string key,
	float animationTimer,
	int startFrameX, int startFrameY, int framesX, int framesY,
	int width, int height) {
	
	this->animations[key] = new Animation(
		this->sprite, this->texture,
		animationTimer,
		startFrameX, startFrameY, framesX, framesY, width, height
	);
}

const bool AnimationComponent::play(const std::string key, const float dt, const bool priority) {
	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == NULL) {
					this->lastAnimation = this->animations[key];
				} else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			if (this->animations[key]->play(dt)) {
				this->priorityAnimation = NULL;
			}
		}
	} else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == NULL) {
				this->lastAnimation = this->animations[key];
			} else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool AnimationComponent::play(const std::string key, const float dt,
		const float modifier, const float modifier_max, const bool priority) {

	if (this->priorityAnimation) {
		if (this->priorityAnimation == this->animations[key]) {
			if (this->lastAnimation != this->animations[key]) {
				if (this->lastAnimation == NULL) {
					this->lastAnimation = this->animations[key];
				} else {
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			if (this->animations[key]->play(dt, abs(modifier / modifier_max))) {
				this->priorityAnimation = NULL;
			}
		}
	} else {
		if (priority) {
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key]) {
			if (this->lastAnimation == NULL) {
				this->lastAnimation = this->animations[key];
			} else {
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}
	}

	return this->animations[key]->isDone();
}
