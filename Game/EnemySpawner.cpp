#include "stdafx.h"
#include "EnemySpawner.h"

EnemySpawner::EnemySpawner(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision, short type)
	: Tile(x, y, gridSizeF, texture, rect, false, Tile_types::ENEMYSPAWNER)
{
	this->tileShape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->tileShape.setTexture(*texture);
	this->tileShape.setTextureRect(rect);

	this->collision = collision;
	this->type = type;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update()
{

}

void EnemySpawner::render(sf::RenderTarget& target, const sf::Vector2f playerPos, sf::Shader* shader)	
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", playerPos);

		target.draw(this->tileShape, shader);
	}
	else
	{
		target.draw(this->tileShape);
	}
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
}
