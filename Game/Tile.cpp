#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(float x, float y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect)
{
	this->tileShape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->tileShape.setFillColor(sf::Color::White);
	this->tileShape.setPosition(x, y);
	this->tileShape.setTexture(texture);
	this->tileShape.setTextureRect(rect);
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
