#pragma once
#include "Item.h"
class Weapon :
    public Item
{
public:
    Weapon(unsigned value, std::string file);
    Weapon(unsigned minDmg, unsigned maxDmg, unsigned range, unsigned value, std::string file);
    virtual ~Weapon();

    virtual Item* clone() = 0;

    virtual void update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter) = 0;
    virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

    const unsigned& getRange() const;

    const unsigned& getMinDmg() const;
    const unsigned& getDmg() const;
    const unsigned& getMaxDmg() const;

    const bool getAttackTimer();

protected:

    unsigned range;

    sf::Texture weaponTexture;
    sf::Sprite weaponSprite;

    unsigned minDmg;
    unsigned maxDmg;

    float CD;
    float maxCD;
    float CDiteration;

    sf::Clock attackTimer;
    sf::Int32 attackTimerMax;   


private:
    void initVars();
    void initCD();
};

