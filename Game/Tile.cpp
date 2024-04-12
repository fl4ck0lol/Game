#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->colliding = false;
	this->type = 0;
}

Tile::Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool colliding, short unsigned type)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setFillColor(sf::Color::White);
	this->tileShape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->tileShape.setTexture(texture);
	this->tileShape.setTextureRect(rect);

	this->colliding = colliding;
	this->type = type;
}

Tile::~Tile()
{
}

void Tile::update()
{

}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->tileShape);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->tileShape.getTextureRect().left << " " << tileShape.getTextureRect().top << " " << this->colliding << " " << this->type;

	return ss.str();
}
