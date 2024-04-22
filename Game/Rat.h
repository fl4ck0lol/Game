#pragma once
#include "allEnemy.h"
#include "GUI.h"
#include "Entity.h"

class Enemy;

class Rat : public Enemy
{
public:

    Rat(sf::Texture& textureSheet, float x, float y);
    virtual ~Rat();


    void update(const float& dt, sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, Entity* player = nullptr, const bool showHitbox = false);

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

    AttributeComponent* getAtrComp();


private:

    bool attacking;
    GUI::ProgressBar* healthBar;

    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);

    void InitialiseVariables();
    void InitialiseAnimations();
    void InitialiseBar();
    void InitialiseAI();
};

