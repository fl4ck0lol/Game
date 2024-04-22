#pragma once
#include "allEnemy.h"
class AiOption
{
protected:
	Entity& entity;
	Entity& self;

public:
	AiOption(Entity* self, Entity& entity);
	virtual ~AiOption();

	virtual void update() = 0;
};

