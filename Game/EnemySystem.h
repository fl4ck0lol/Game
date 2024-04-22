#pragma once
#include "Enemy.h"
#include "Rat.h"

enum enemyTypes{RAT = 0};

class EnemySystem
{
public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures, Entity& player);
	virtual ~EnemySystem();

	void createEnemy(const short type, const float x, const float y, EnemySpawner& es);

	void update(const float& dt);
	void render(sf::RenderTarget* target);
	void removeEnemy(const int index);

private:

	Entity& player;

	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
};

