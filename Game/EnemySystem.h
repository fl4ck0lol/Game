#pragma once
#include "allEnemy.h"

enum enemyTypes{RAT = 0};

class EnemySystem
{
public:
	EnemySystem(std::vector<Enemy*>& activeEnemies, std::map<std::string, sf::Texture>& textures);
	virtual ~EnemySystem();

	void createEnemy(const short type, const float x, const float y);

	void update(const float& dt);
	void render(sf::RenderTarget* target);

private:
	std::map<std::string, sf::Texture>& textures;
	std::vector<Enemy*>& activeEnemies;
};

