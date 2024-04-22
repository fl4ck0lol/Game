#include "stdafx.h"
#include "Sword.h"

Sword::Sword(unsigned minDmg, unsigned maxDmg, unsigned range, unsigned value, std::string file) : MeleeWeapon(minDmg, maxDmg, range, value, file)
{

	this->weaponSprite.setTexture(weaponTexture);

	this->weaponSprite.setOrigin(this->weaponSprite.getGlobalBounds().width / 2.f, this->weaponSprite.getGlobalBounds().height);
}

Sword::~Sword()
{
}

void Sword::update(sf::Vector2f mousePosView, const sf::Vector2f getPlayerCenter)
{
	this->weaponSprite.setPosition(getPlayerCenter.x, getPlayerCenter.y);

	float dx = mousePosView.x - this->weaponSprite.getPosition().x;
	float dy = mousePosView.y - this->weaponSprite.getPosition().y;

	const float pi = 3.14159265f;
	float deg = atan2(dy, dx) * 180.f / pi;

	this->weaponSprite.setRotation(deg + 90.f);
}

void Sword::render(sf::RenderTarget& target, sf::Shader* shader)
{
	if(shader)
		target.draw(this->weaponSprite, shader);
	else
		target.draw(this->weaponSprite);
}

Sword* Sword::clone()
{
	return new Sword(*this);
}
