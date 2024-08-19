#pragma once

class Entity;

class AIComponent {
protected:
	Entity			*self;
	Entity			*entity;
public:
	AIComponent(Entity *self, Entity *entity);
	virtual ~AIComponent();

	// Funcs
	virtual	void			execute() = 0;

	// Core
	virtual void			update(const float dt) = 0;
};

#include "Entity.h"
