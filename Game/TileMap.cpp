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
	this->maxSizeWorld.x = static_cast<float>(width) * gridSize;
	this->maxSizeWorld.y = static_cast<float>(height) * gridSize;
	this->layers = 1;
	this->fileName = fileName;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	
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

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
}

TileMap::~TileMap()
{
	this->clear();
}

void TileMap::update()
{

}

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity)
	{
		this->layer = 0;

		this->fromX = entity->getGridPos(this->gridSizeU).x - 1;
		if (this->fromX < 0)
			this->fromX = 0;
		if (this->fromX >= this->maxSizeWorld.x)
			this->fromX = this->maxSizeWorld.x;

		this->toX = entity->getGridPos(this->gridSizeU).x + 2;
		if (this->toX < 0)
			this->toX = 0;
		if (this->toX >= this->maxSizeWorld.x / this->gridSizeU)
			this->toX = this->maxSizeWorld.x / this->gridSizeU;

		this->fromY = entity->getGridPos(this->gridSizeU).y - 1;
		if (this->fromY < 0)
			this->fromY = 0;
		if (this->fromY >= this->maxSizeWorld.y)
			this->fromY = this->maxSizeWorld.y ;

		this->toY = entity->getGridPos(this->gridSizeU).y + 2;
		if (this->toY < 0)
			this->toY = 0;
		if (this->toY >= this->maxSizeWorld.y / this->gridSizeU)
			this->toY = this->maxSizeWorld.y / this->gridSizeU;

		for (size_t x = this->fromX; x < this->toX; x++)
		{
			for (size_t y = this->fromY; y < this->toY; y++)
			{
				if (this->map[x][y][this->layer] != NULL)
				{
					this->map[x][y][this->layer]->render(target);
					if (this->map[x][y][this->layer]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}

		}
	}
	else
	{
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto& z : y)
				{
					if (z != nullptr)
					{
						z->render(target);
						if (z->getCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
	}

}

void TileMap::AddTile(const unsigned x, const unsigned y, const unsigned z, const sf::IntRect& rect, const bool collision, const short type)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, &this->tileTexture, rect, collision, type);
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
		bool collision = 0;
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

		while (inFile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, &this->tileTexture, sf::IntRect(trX, trY, this->gridSizeU, this->gridSizeU), collision, type);
			std::cout << "tile loaded \n";
		}
	}
	else
		std::cout << "Tile map not loaded: " << path;

	inFile.close();
}

void TileMap::updateCollision(Entity* entity)
{
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().x > this->maxSizeWorld.x - entity->getGlobalBounds().width)
	{
		entity->setPosition(this->maxSizeWorld.x - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f)
	{
		entity->setPosition(entity->getPosition().x, 0.f);
		entity->stopVelocityY();
	}

	if (entity->getPosition().y + entity->getGlobalBounds().height > this->maxSizeWorld.y)
	{
		entity->setPosition(entity->getPosition().x, this->maxSizeWorld.y - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	this->fromX = entity->getGridPos(this->gridSizeU).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSizeWorld.x)
		this->fromX = this->maxSizeWorld.x;
	
	this->toX = entity->getGridPos(this->gridSizeU).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSizeWorld.x)
		this->toX = this->maxSizeWorld.x;

	this->fromY = entity->getGridPos(this->gridSizeU).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSizeWorld.y)
		this->fromY = this->maxSizeWorld.y;

	this->toY = entity->getGridPos(this->gridSizeU).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->fromY > this->maxSizeWorld.y)
		this->toY = this->maxSizeWorld.y;



	for (size_t x = this->fromX; x < this->toX; x++)
	{
		for (size_t y = this->fromY; y < this->toY; y++)
		{
			if (this->map[x][y][this->layer]->intersects(entity->getGlobalBounds()) && this->map[x][y][this->layer]->getCollision())
			{
				std::cout << "collision \n";
			}
		}

	}
}
