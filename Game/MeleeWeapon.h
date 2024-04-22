#pragma once
#include "Weapon.h"

class MeleeWeapon : public Weapon
{
private:

protected:

public:
	MeleeWeapon(unsigned minDmg, unsigned maxDmg, unsigned range, unsigned value, std::string file);
	virtual ~MeleeWeapon();

	virtual void update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;

	virtual MeleeWeapon* clone() = 0;
};

