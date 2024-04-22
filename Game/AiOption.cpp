#include "stdafx.h"
#include "AiOption.h"

AiOption::AiOption(Entity* self, Entity& entity) : self(*self), entity(entity)
{
}

AiOption::~AiOption()
{
}
