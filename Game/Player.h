#pragma once
#include "Entity.h"
#include "items.h"
#include "TileMap.h"

class Player :
    public Entity
{
public:
    Player(sf::Texture& texture, float x, float y);
    ~Player();

    void update(const float& dt, sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, Entity* entity = nullptr, const bool showHitbox = false);

    AttributeComponent* getAtrComp();

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

    Weapon* getWeapon() const;

private:
    Sword* sword;
    bool attacking;


    void InitialiseVariables();

    void InitialiseAnimations();
    void updateAnimation(const float& dt);

};

