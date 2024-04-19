#pragma once
#include "MeleeWeapon.h"
class Sword :
    public MeleeWeapon
{
public:
    Sword();
    virtual ~Sword();

    virtual void update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

};

