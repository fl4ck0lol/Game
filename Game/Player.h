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

    AttributeComponent* getAtrComp();

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

private:

    bool attacking;
    void InitialiseVariables();

    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);

};

