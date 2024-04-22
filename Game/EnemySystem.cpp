#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player) : textures(textures), activeEnemies(activeEnemies), player(player)
{

}

EnemySystem::~EnemySystem()
{
}

void EnemySystem::createEnemy(const short type, const float x, const float y, EnemySpawner& es)
{
	switch (type)
	{
	case enemyTypes::RAT:
		this->activeEnemies.push_back(new Rat(this->textures["RAT"], x, y, es, this->player));
		es.increaseEnemyCounter();
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

void EnemySystem::removeEnemy(const int index)
{
	this->activeEnemies[index]->getSpawner().decreaseEnemyCounter();

	delete this->activeEnemies[index];
	this->activeEnemies.erase(this->activeEnemies.begin() + index);
}
