#pragma once
#include "AiOption.h"

class AiFollow :
    public AiOption
{
private:

public:
    AiFollow(Entity& self, Entity& entity);
    ~AiFollow();

    void update(const float& dt);
};

