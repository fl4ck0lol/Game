#pragma once
#include"allEnemy.h"
#include"Tile.h"

class Tile;
class Enemy;
class Rat;

class EnemySpawner : public Tile
{
private:
	
	std::map<std::string, sf::Texture> textures;
	std::vector<Rat*> enemies;

	sf::Sprite tileShape;
	bool collision;
	short unsigned type;
	short unsigned enemyType;

	int enemyAmount;
	int enemyCounter;
	sf::Clock enemySpawnTimer;
	sf::Int32 enemyTimeToSpawn;
	bool firstSpawn;
	
	void InitVars();

	bool spawned;

public:
	EnemySpawner(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision = false, short type = 3, short enemyType = 0);
	~EnemySpawner();

	void update();
	void render(sf::RenderTarget& target, const sf::Vector2f playerPos = sf::Vector2f(), sf::Shader* shader = nullptr);

	void spawn();
	void clear();
	const std::string getEnemySpawnerAsString() const;

	void setSpawned(const bool spawned);

	const bool& getSpawned();

	const bool canSpawn() const;
};

