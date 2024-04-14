#pragma once
#include "Entity.h"
class Player :
    public Entity
{
public:
    Player(sf::Texture& texture, float x, float y);
    ~Player();

    void update(const float& dt);
    void render(sf::RenderTarget& target);

private:

    bool attacking;
    void InitialiseVariables();

};

