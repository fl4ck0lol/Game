#include "stdafx.h"
#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height)
	: sprite(sprite), offset_x(offset_x), offset_y(offset_y)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x, this->sprite.getPosition().y + this->offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
}

HitboxComponent::~HitboxComponent()
{
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offset_x, this->sprite.getPosition().y + this->offset_x);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}

bool HitboxComponent::checkCollision(const sf::FloatRect& collision)
{
	if (this->hitbox.getGlobalBounds().intersects(collision))
		return true;
	return false;
}
