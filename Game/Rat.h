#pragma once
#include "Enemy.h"
class Rat :
    public Enemy
{
public:
    Rat(sf::Texture& textureSheet, float x, float y);
    virtual ~Rat();


    void update(const float& dt, sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool showHitbox = false);

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

    AttributeComponent* getAtrComp();

private:

    bool attacking;

    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);

    void InitialiseVariables();
    void InitialiseAnimations();

};

