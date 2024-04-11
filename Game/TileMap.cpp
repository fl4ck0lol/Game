#include "stdafx.h"
#include "TileMap.h"

TileMap::TileMap(float gridSize, unsigned width, unsigned height)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	
	this->map.resize(this->maxSize.x,std::vector<std::vector<Tile*>>());
	for (size_t x = 0; x < this->maxSize.x; x++)
	{
		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, nullptr);
			}
		}
	}

	this->tileTexture.loadFromFile("Resources/GRASS+.png");
}

TileMap::~TileMap()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
			}
		}
	}
}


void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if(z != nullptr)
					z->render(target);
			}
		}
	}
}

void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x * this->gridSizeF, y * this->gridSizeF, this->gridSizeF, &this->tileTexture, rect);
			std::cout << "added tile \n";
		}
		else
			std::cout << "cannot duplicate \n";
	}
}

void TileMap::RemoveTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
			std::cout << "removed tile \n";
		}
		else
			std::cout << "cannot remove nonexisting \n";
	}
}

const sf::Texture* TileMap::getTileTexture() const
{
	return &this->tileTexture;
}
