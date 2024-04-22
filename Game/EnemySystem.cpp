#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures) : textures(textures), activeEnemies(activeEnemies)
{

}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float x, const float y)
{
	switch (type)
	{
	case enemyTypes::RAT:
		this->activeEnemies.push_back(new Rat(this->textures["RAT"], x, y));
		break;
	default:
		std::cout << "type doesnt exist";
		break;
	}
}

void EnemySystem::update(const float& dt)
{
}

void EnemySystem::render(sf::RenderTarget* target)
{
}
