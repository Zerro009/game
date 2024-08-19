#pragma once

#include "AIComponent.h"

class AIFollow : public AIComponent {
private:

public:
	AIFollow(Entity *self, Entity *entity);
	virtual ~AIFollow();

	// Funcs
	void			execute();

	// Core
	void			update(const float dt);
};
