#pragma once
#include "Tile.h"
#include "EnemySpawner.h"
#include "allEnemy.h"
#include "EnemySystem.h"

class Tile;
class EnemySpawner;

class TileMap
{
private:
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;
	sf::Vector2i maxSize;
	int gridSizeI;
	float gridSizeF;
	int layers;
	std::string fileName;

	std::vector<Enemy*> activeEnemies;

	sf::Texture tileTexture;

	sf::RectangleShape collisionBox;
	sf::RectangleShape Spawner;

	void clear();

	sf::Vector2f maxSizeWorld;
	sf::Vector2i maxSizeWorldGrid;

	std::stack<Tile*> deferredStack;

	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;


protected:
	

public:

	TileMap(float gridSize, int width, int height, std::string fileName);

	TileMap(const std::string path);

	virtual ~TileMap();

	void render(sf::RenderTarget& target, const sf::Vector2i& gridPos, sf::Shader* shader = nullptr, const bool showCollision = false, const sf::Vector2f playerPos = sf::Vector2f());

	void AddTile(const int x, const int y, const int z, const sf::IntRect& rect, const bool collision, const short type, const short enemyType = 0);
	void RemoveTile(const int x, const int y, const int z);

	const sf::Texture* getTileTexture() const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	void update(Entity* entity, const float& dt);

	const int getTileAmount(const int x, const int y, const int layer) const;

	void renderDeferred(sf::RenderTarget& target, const sf::Vector2f gridPos = sf::Vector2f(), sf::Shader* shader = nullptr);

	const sf::Vector2i& getMaxSizeGrid() const;
	const sf::Vector2f& getMaxSizeF() const;

	const bool tileEmpty(const int x, const int y, const int z) const;

	void updateTiles(Entity* entity, const float& dt, EnemySystem& enemySystem);
	void updateWorldBoundsCollision(Entity* entity, const float& dt);
	void updateTileCollision(Entity* entity, const float& dt);
};

