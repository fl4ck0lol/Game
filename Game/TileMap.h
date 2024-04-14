#pragma once
#include "Tile.h"
#include "Entity.h"

class Tile;
class Entity;

class TileMap
{
private:
	std::vector<std::vector<std::vector<Tile*>>> map;
	sf::Vector2u maxSize;
	unsigned gridSizeU;
	float gridSizeF;
	unsigned layers;
	std::string fileName;

	sf::Texture tileTexture;

	sf::RectangleShape collisionBox;

	void clear();

	sf::Vector2f maxSizeWorld;

protected:
	

public:

	TileMap(float gridSize, unsigned width, unsigned height, std::string fileName);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target, Entity* entity = nullptr);

	void AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect, const bool collision, const short type);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getTileTexture() const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);

	void updateCollision(Entity* entity);
};

