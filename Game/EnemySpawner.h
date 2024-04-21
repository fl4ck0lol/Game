#pragma once
#include"Enemy.h"
#include"Tile.h"

class Tile;
class Enemy;

class EnemySpawner : public Tile
{
private:
	
	sf::Sprite tileShape;
	bool collision;
	short unsigned type;
	short unsigned enemyType;


public:
	EnemySpawner(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision = false, short type = 3, short enemyType = 0);
	~EnemySpawner();

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2f playerPos = sf::Vector2f(), sf::Shader* shader = nullptr);

	void spawn();
	void clear();
};

