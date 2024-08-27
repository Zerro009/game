#pragma once

#include "pch.h"

class AnimationComponent {
private:
	class Animation {
	public:
		sf::Sprite	*sprite;
		sf::Texture	*texture;
		float		animationTimer;
		float		timer;
		bool		done;
		int		width;
		int		height;
		sf::IntRect	startRect;
		sf::IntRect	currentRect;
		sf::IntRect	endRect;

		Animation(sf::Sprite *sprite, sf::Texture *texture,
				float animationTimer, int startFrameX, int startFrameY,
				int framesX, int framesY, int width, int height
			) : sprite(sprite), texture(texture), animationTimer(animationTimer),
				timer(0.f), done(false), width(width), height(height)
		{
			this->startRect = sf::IntRect(startFrameX * width, startFrameY * height, width, height);
			this->currentRect = this->startRect;
			this->endRect = sf::IntRect(framesX * width, framesY * height, width, height);

			this->sprite->setTexture(*this->texture, true);
			this->sprite->setTextureRect(this->startRect);
		}

		// Accessor
		const bool isDone() const {
			return this->done;
		}

		// Funcs
		const bool play(const float dt) {
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= this->animationTimer) {
				// Reset timer
				this->timer = 0.f;

				// Animate
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				} else {
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite->setTextureRect(this->currentRect);
			}
			return this->done;
		}

		const bool play(const float dt, float mod_percent) {
			if (mod_percent < 0.5f) {
				mod_percent = 0.5f;
			}

			this->done = false;
			this->timer += mod_percent * 100.f * dt;

			if (this->timer >= this->animationTimer) {
				// Reset timer
				this->timer = 0.f;

				// Animate
				if (this->currentRect != this->endRect) {
					this->currentRect.left += this->width;
				} else {
					this->currentRect.left = this->startRect.left;
					this->done = true;
				}

				this->sprite->setTextureRect(this->currentRect);
			}
			return this->done;
		}

		void reset() {
			this->timer = this->animationTimer;
			this->currentRect = this->startRect;
		}
	};

	sf::Sprite				*sprite;
	sf::Texture				*texture;
	std::map<std::string, Animation*>	animations;
	Animation				*lastAnimation;
	Animation				*priorityAnimation;

public:
	AnimationComponent(sf::Sprite *sprite, sf::Texture *texture);
	virtual ~AnimationComponent();

	// Accessors
	const bool				isDone(const std::string key);

	// Funcs
	void					addAnimation(const std::string key,
							float animationTimer,
							int startFrameX, int startFrameY,
							int framesX, int framesY, int width, int height);
	const bool				play(const std::string key, const float dt, const bool priority=false);
	const bool				play(const std::string key, const float dt,
							const float modifier, const float modifier_max,
							const bool priority = false);
};
