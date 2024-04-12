#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; x++)
	{

		for (size_t y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].push_back(std::vector<Tile*>());

			for (size_t z = 0; z < this->layers; z++)
			{
				delete this->map[x][y][z];
				this->map[x][y][z] = nullptr;
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}

	this->map.clear();

}

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string fileName)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = static_cast<unsigned>(this->gridSizeF);
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->fileName = fileName;
	
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

	if (!this->tileTexture.loadFromFile(this->fileName))
		std::cout << "Texture didnt load: " << this->fileName;
}

TileMap::~TileMap()
{
	this->clear();
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
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, &this->tileTexture, rect);
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

void TileMap::saveToFile(const std::string path)
{
	/*file format:
	Size x y
	gridSize
	layers
	texture file
	-------------------------------
	gridPos x y layer, textureRect x y, colliding, type
	
	*/

	std::ofstream OutFile;

	OutFile.open(path);

	if (OutFile.is_open())
	{
		OutFile << this->maxSize.x << " " << this->maxSize.y << "\n";
		OutFile << this->gridSizeU << "\n";
		OutFile << this->layers << "\n";
		OutFile << this->fileName << "\n";

		for (size_t x = 0; x < this->maxSize.x; x++)
		{

			for (size_t y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].push_back(std::vector<Tile*>());

				for (size_t z = 0; z < this->layers; z++)
				{
					if(this->map[x][y][z])
						OutFile << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << "\n";
				}
			}
		}
	}
	else
		std::cout << "Tile map not saved: " << path;

	OutFile.close();

}


void TileMap::loadFromFile(const std::string path)
{

	std::ifstream inFile;

	inFile.open(path);

	if (inFile.is_open())
	{
		sf::Vector2u size;
		unsigned gridSize = 0;	
		unsigned layers = 0;
		std::string fileName = "";
		unsigned x = 0;
		unsigned y = 0;
		unsigned z = 0;
		unsigned trX = 0;
		unsigned trY = 0;
		bool colliding = 0;
		short type = 0;

		inFile >> size.x >> size.y >> gridSize >> layers >> fileName;

		this->gridSizeF =static_cast<float>(gridSize);
		this->gridSizeU = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->fileName = fileName;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector<std::vector<Tile*>>());
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

		if (!this->tileTexture.loadFromFile(this->fileName))
			std::cout << "Texture didnt load: " << this->fileName;

		while (inFile >> x >> y >> z >> trX >> trY >> colliding >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, &this->tileTexture, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), colliding, type);
			std::cout << "tile loaded \n";
		}
	}
	else
		std::cout << "Tile map not loaded: " << path;

	inFile.close();
}
