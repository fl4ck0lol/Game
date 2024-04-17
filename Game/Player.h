#pragma once
#include "Entity.h"
class Player :
    public Entity
{
public:
    Player(sf::Texture& texture, float x, float y);
    ~Player();

    void update(const float& dt, sf::Vector2f& mousePos);
    void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, const bool showHitbox = false);

    AttributeComponent* getAtrComp();

    void loseHP(const int hp);
    void loseXP(const int xp);
    void gainHP(const int hp);
    void gainXP(const int xp);

private:

    sf::Sprite weaponSprite;
    sf::Texture weaponTexture;
    bool attacking;
    void InitialiseVariables();

    void updateAttack(const float& dt);
    void updateAnimation(const float& dt);

};

