#pragma once
#include "Tile.h"



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

	void clear();

protected:
	

public:

	TileMap(float gridSize, unsigned width, unsigned height, std::string fileName);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getTileTexture() const;

	void saveToFile(const std::string path);
	void loadFromFile(const std::string path);
};

