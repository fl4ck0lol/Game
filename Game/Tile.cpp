#include "stdafx.h"
#include "Tile.h"

Tile::Tile()
{
	this->collision = false;
	this->type = 0;
}

Tile::Tile(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision, short type)
{
	this->tileShape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->tileShape.setTexture(*texture);
	this->tileShape.setTextureRect(rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{

}

void Tile::update()
{
	
}

void Tile::render(sf::RenderTarget& target, const sf::Vector2f playerPos, sf::Shader* shader)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->tileShape, shader);
	}
	else
		target.draw(this->tileShape);
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;

	ss << this->tileShape.getTextureRect().left << " " << tileShape.getTextureRect().top << " " << this->collision << " " << this->type;

	return ss.str();
}

const sf::Vector2f& Tile::getPosition() const
{
	return this->tileShape.getPosition();
}

const sf::FloatRect Tile::getGlobalBounds()
{
	return this->tileShape.getGlobalBounds();
}

const bool& Tile::getCollision() const
{
	return this->collision;
}

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->tileShape.getGlobalBounds().intersects(bounds);
}

const short& Tile::getType() const
{
	return this->type;
}

const bool Tile::SpawnerType() const
{
	if (this->type == ENEMYSPAWNER)
	{
		return true;
	} 
	else
		return false;
}