#include "stdafx.h"
#include "EnemySpawner.h"

void EnemySpawner::InitVars()
{
	this->enemyAmount = 5;
	this->enemyCounter = 0;
	this->enemySpawnTimer.restart();
	this->enemyTimeToSpawn = 5000;
	this->firstSpawn = true;
}

EnemySpawner::EnemySpawner(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision, short type, short enemyType)
	: Tile(x, y, gridSizeF, texture, rect, false, Tile_types::ENEMYSPAWNER, enemyType)
{
	this->InitVars();

	this->tileShape.setPosition(static_cast<float>(x) * gridSizeF, static_cast<float>(y) * gridSizeF);
	this->tileShape.setTexture(*texture);
	this->tileShape.setTextureRect(rect);

	this->collision = collision;
	this->type = type;
	this->enemyType = enemyType;

	this->spawned = false;
}

EnemySpawner::~EnemySpawner()
{
}

void EnemySpawner::update()
{
	if (this->canSpawn())
	{
		this->spawned = false;
	}
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
		target.draw(this->tileShape, shader);
}

void EnemySpawner::spawn()
{
}

void EnemySpawner::clear()
{
}

const std::string EnemySpawner::getEnemySpawnerAsString() const
{
	std::stringstream ss;

	ss << this->tileShape.getTextureRect().left << " " << tileShape.getTextureRect().top << " " << this->collision << " " << this->type << " " << this->enemyType;

	return ss.str();
}

const bool& EnemySpawner::getSpawned()
{
	return this->spawned;
}

const bool EnemySpawner::canSpawn() const
{
	if (this->enemySpawnTimer.getElapsedTime().asMilliseconds() >= this->enemyTimeToSpawn)
	{
		return true;
	}
	return false;
}

void EnemySpawner::setSpawned(const bool spawned)
{
	this->spawned = spawned;
	this->enemySpawnTimer.restart();
}
