#pragma once
#include "AiOption.h"

class AiFollow :
    public AiOption
{
public:
    AiFollow(Entity* self, Entity& entity);
    virtual ~AiFollow();

    void update(const float& dt);
};

