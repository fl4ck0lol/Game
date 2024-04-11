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

	sf::Texture tileTexture;

protected:
	

public:

	TileMap(float gridSize, unsigned width, unsigned height);
	virtual ~TileMap();

	void update();
	void render(sf::RenderTarget& target);

	void AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect);
	void RemoveTile(const unsigned x, const unsigned y, const unsigned z);

	const sf::Texture* getTileTexture() const;
};

