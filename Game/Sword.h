#pragma once
#include "MeleeWeapon.h"
class Sword :
    public MeleeWeapon
{
public:
    Sword(unsigned minDMg, unsigned maxDmg, unsigned range, unsigned value, std::string file);
    virtual ~Sword();

    virtual void update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter);
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr);

    virtual Sword* clone();
};

