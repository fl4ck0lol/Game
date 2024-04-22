#pragma once
#include "Entity.h"

class AiOption
{
protected:
	Entity& entity;
	Entity& self;

public:
	AiOption(Entity& self, Entity& entity) : self(self), entity(entity)
	{

	}

	virtual void update(const float& dt) = 0;
};

