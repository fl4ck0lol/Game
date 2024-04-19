#pragma once
#include "Item.h"
class MeleeWeapon : public Item
{
private:

protected:
	sf::Texture weaponTexture;
	sf::Sprite weaponSprite;

	int minDmg;
	int maxDmg;

public:
	MeleeWeapon();
	virtual ~MeleeWeapon();

	virtual void update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr) = 0;
};

