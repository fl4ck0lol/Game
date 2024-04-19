#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class EnemySpawner;

class Enemy :
    public Entity
{
private:

    bool attacking;

    void updateAttack(const float& dt);
    virtual void updateAnimation(const float& dt) = 0;

    virtual void InitialiseVariables() = 0;
    virtual void InitialiseAnimations() = 0;

public:

    Enemy();
    virtual ~Enemy();

    virtual void update(const float& dt, sf::Vector2f& mousePos) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool showHitbox = false) = 0;

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

    AttributeComponent* getAtrComp();
};

