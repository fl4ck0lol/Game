#pragma once
#include "Entity.h"

class EnemySpawner;

class Enemy :
    public Entity
{
private:

    EnemySpawner& enemySpawner;

    bool attacking;
    unsigned xp;

    void updateAttack(const float& dt);
    virtual void updateAnimation(const float& dt) = 0;

    virtual void InitialiseVariables() = 0;
    virtual void InitialiseAnimations() = 0;

public:

    Enemy(EnemySpawner& enemySpawner);
    virtual ~Enemy();


    virtual void update(const float& dt, sf::Vector2f& mousePos) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, Entity* entity = nullptr, const bool showHitbox = false) = 0;

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

    AttributeComponent* getAtrComp();

    virtual void loseHp(const int dmg);

    const virtual AttributeComponent* GetAtrComp() const;

    virtual const bool isDead() const;

    virtual const unsigned& giveXp() const;

    EnemySpawner& getSpawner();
};

