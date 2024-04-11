#pragma once
#include "Entity.h"
class Player :
    public Entity
{
public:
    Player(sf::Texture& texture, float x, float y);
    ~Player();

    virtual void update(const float& dt);

private:

    bool attacking;
    void InitialiseVariables();

};

