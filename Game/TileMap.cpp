#include "stdafx.h"
#include "TileMap.h"

void TileMap::clear()
{
	if (!this->map.empty())
	{

		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					for (int k = 0; k < this->map[x][y][z].size(); k++)
					{
						delete this->map[x][y][z][k];
						this->map[x][y][z][k] = nullptr;
					}
					this->map[x][y][z].clear();
				}
				this->map[x][y].clear();
			}
			this->map[x].clear();
		}

		this->map.clear();
	}
}

TileMap::TileMap(float gridSize, int width, int height, std::string fileName)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = static_cast<int>(this->gridSizeF);
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

	
	this->map.resize(this->maxSize.x,std::vector<std::vector<std::vector<Tile*>>>());
	for (int x = 0; x < this->maxSize.x; x++)
	{
		for (int y = 0; y < this->maxSize.y; y++)
		{
			this->map[x].resize(this->maxSize.y, std::vector<std::vector<Tile*>>());

			for (int z = 0; z < this->layers; z++)
			{
				this->map[x][y].resize(this->layers, std::vector<Tile*>());
			}
		}
	}

	if (!this->tileTexture.loadFromFile(this->fileName))
		std::cout << "Texture didnt load: " << this->fileName;

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));

	this->Spawner.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->Spawner.setFillColor(sf::Color(0, 0, 255, 50));
}

TileMap::TileMap(const std::string path)
{
	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->loadFromFile(path);

	this->collisionBox.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));

	this->Spawner.setSize(sf::Vector2f(this->gridSizeF, this->gridSizeF));
	this->Spawner.setFillColor(sf::Color(0, 0, 255, 50));
}

TileMap::~TileMap()
{
	this->clear();
}

void TileMap::render(sf::RenderTarget& target, const sf::Vector2i& gridPos, sf::Shader* shader, const bool showCollision, const sf::Vector2f playerPos)
{

		this->layer = 0;

		this->fromX = gridPos.x - 14;
		if (this->fromX < 0)
			this->fromX = 0;
		if (this->fromX >= this->maxSize.x)
			this->fromX = this->maxSize.x;

		this->toX = gridPos.x + 15;
		if (this->toX < 0)
			this->toX = 0;
		if (this->toX >= this->maxSize.x)
			this->toX = this->maxSize.x;

		this->fromY = gridPos.y - 8;
		if (this->fromY < 0)
			this->fromY = 0;
		if (this->fromY >= this->maxSize.y)
			this->fromY = this->maxSize.y;

		this->toY = gridPos.y + 9;
		if (this->toY < 0)
			this->toY = 0;
		if (this->toY >= this->maxSize.y)
			this->toY = this->maxSize.y;

		for (size_t x = this->fromX; x < this->toX; x++)
		{
			for (size_t y = this->fromY; y < this->toY; y++)
			{
				for (int k = 0; k < this->map[x][y][this->layer].size(); k++)
				{
					if (this->map[x][y][this->layer][k]->getType() == Tile_types::DOODAD)
					{
						this->deferredStack.push(this->map[x][y][this->layer][k]);
					}
					else
					{
						if (shader)
							this->map[x][y][this->layer][k]->render(target, playerPos, shader);
						else
							this->map[x][y][this->layer][k]->render(target);

						if (this->map[x][y][this->layer][k]->getType() == Tile_types::ENEMYSPAWNER)
						{
							if(shader)
								this->map[x][y][this->layer][k]->render(target, playerPos, shader);
							else
								this->map[x][y][this->layer][k]->render(target);
						}
					}

					if (showCollision)
					{
						if (this->map[x][y][this->layer][k]->getCollision())
						{
							this->collisionBox.setPosition(this->map[x][y][this->layer][k]->getPosition());
							target.draw(this->collisionBox);
						}
					}
					if (this->map[x][y][this->layer][k]->SpawnerType())
					{
						this->Spawner.setPosition(this->map[x][y][this->layer][k]->getPosition());
						target.draw(this->Spawner);
					}
				}

			}

		}
}

void TileMap::AddTile(const int x, const int y, const int z, const sf::IntRect& rect, const bool collision, const short type, const short enemyType)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (type == ENEMYSPAWNER)
		{
			this->map[x][y][z].push_back(new EnemySpawner(x, y, this->gridSizeF, &this->tileTexture, rect, collision, type, enemyType));
			std::cout << "added enemy spawner \n";
		}
		else
		{
			this->map[x][y][z].push_back(new Tile(x, y, this->gridSizeF, &this->tileTexture, rect, collision, type));
			std::cout << "added tile \n";
		}
	}
}

void TileMap::RemoveTile(const int x, const int y, const int z)
{
	if (x < this->maxSize.x && x >= 0 && y < this->maxSize.y && y >= 0 && z < this->layers && z >= 0)
	{
		if (!this->map[x][y][z].empty())
		{
			delete this->map[x][y][z][this->map[x][y][z].size() - 1];
			this->map[x][y][z].pop_back();
			std::cout << "removed tile \n";
		}
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
		OutFile << this->gridSizeI << "\n";
		OutFile << this->layers << "\n";
		OutFile << this->fileName << "\n";

		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
				for (int z = 0; z < this->layers; z++)
				{
					if (!this->map[x][y][z].empty())
					{
						for (int k = 0; k < this->map[x][y][z].size(); k++)
						{
							OutFile << x << " " << y << " " << z << " " << this->map[x][y][z][k]->getAsString() << "\n";
						}
					}
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
		sf::Vector2i size;
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

		this->gridSizeF = static_cast<float>(gridSize);
		this->gridSizeI = gridSize;
		this->maxSize.x = size.x;
		this->maxSize.y = size.y;
		this->layers = layers;
		this->fileName = fileName;

		this->clear();

		this->map.resize(this->maxSize.x, std::vector<std::vector<std::vector<Tile*>>>());
		for (int x = 0; x < this->maxSize.x; x++)
		{
			for (int y = 0; y < this->maxSize.y; y++)
			{
				this->map[x].resize(this->maxSize.y, std::vector<std::vector<Tile*>>());

				for (int z = 0; z < this->layers; z++)
				{
					this->map[x][y].resize(this->layers, std::vector<Tile*>());
				}
			}
		}

		if (!this->tileTexture.loadFromFile(this->fileName))
			std::cout << "Texture didnt load: " << this->fileName;

		while (inFile >> x >> y >> z >> trX >> trY >> collision >> type)
		{
			this->map[x][y][z].push_back(new Tile
			(x, y, this->gridSizeF, &this->tileTexture, sf::IntRect(trX, trY, this->gridSizeI, this->gridSizeI), collision, type));
		}
	}
	else
		std::cout << "Tile map not loaded: " << path;

	inFile.close();
}

void TileMap::update(Entity* entity, const float& dt)
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

	this->fromX = entity->getGridPos(this->gridSizeI).x - 1;
	if (this->fromX < 0)
		this->fromX = 0;
	else if (this->fromX > this->maxSize.x)
		this->fromX = this->maxSize.x;
	
	this->toX = entity->getGridPos(this->gridSizeI).x + 3;
	if (this->toX < 0)
		this->toX = 0;
	else if (this->toX > this->maxSize.x)
		this->toX = this->maxSize.x;

	this->fromY = entity->getGridPos(this->gridSizeI).y - 1;
	if (this->fromY < 0)
		this->fromY = 0;
	else if (this->fromY > this->maxSize.y)
		this->fromY = this->maxSize.y;

	this->toY = entity->getGridPos(this->gridSizeI).y + 3;
	if (this->toY < 0)
		this->toY = 0;
	else if (this->toY > this->maxSize.y)
		this->toY = this->maxSize.y;


	for (int x = this->fromX; x < this->toX; x++)
	{
		for (int y = this->fromY; y < this->toY; y++)
		{

			for (int k = 0; k < map[x][y][this->layer].size(); k++)
			{
				this->map[x][y][this->layer][k]->update();

				sf::FloatRect playerBounds = entity->getGlobalBounds();
				sf::FloatRect wallBounds = map[x][y][this->layer][k]->getGlobalBounds();
				sf::FloatRect nextPosBounds = entity->getNextPosBounds(dt);

				if (this->map[x][y][this->layer][k]->intersects(nextPosBounds) && this->map[x][y][this->layer][k]->getCollision())
				{
					//Bottom collision
					if (playerBounds.top < wallBounds.top
						&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
						&& playerBounds.left < wallBounds.left + wallBounds.width
						&& playerBounds.left + playerBounds.width > wallBounds.left)
					{
						entity->stopVelocityY();
						entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
					}

					//Top collision
					else if (playerBounds.top > wallBounds.top
							&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
							&& playerBounds.left < wallBounds.left + wallBounds.width
							&& playerBounds.left + playerBounds.width > wallBounds.left)
						 {
							entity->stopVelocityY();
							entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
						 }

					//Right collision
					if (playerBounds.left < wallBounds.left
						&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
						&& playerBounds.top < wallBounds.top + wallBounds.height
						&& playerBounds.top + playerBounds.height > wallBounds.top)
					{
						entity->stopVelocityX();
						entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
					}

					//Left collision
					else if (playerBounds.left > wallBounds.left
							&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
							&& playerBounds.top < wallBounds.top + wallBounds.height
							&& playerBounds.top + playerBounds.height > wallBounds.top)
						 {
							entity->stopVelocityX();
							entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
						 }
				}
			}
		}

	}
}

const int TileMap::getTileAmount(const int x, const int y, const int layer) const
{
	if (x >= 0 && x < this->map.size())
	{	
		if (y >= 0 && y < this->map[x].size())
		{
			if (layer >= 0 && layer < this->map[x][y].size())
			{
				return this->map[x][y][layer].size();
			}
		}
	}
	return 0;
}

void TileMap::renderDeferred(sf::RenderTarget& target, const sf::Vector2f playerPos, sf::Shader* shader)
{
	while (!this->deferredStack.empty())
	{
		if (shader)
			deferredStack.top()->render(target, playerPos, shader);
		else
			deferredStack.top()->render(target);

		deferredStack.pop();
	}
}

const sf::Vector2i& TileMap::getMaxSizeGrid() const
{
	return this->maxSize;
}

const sf::Vector2f& TileMap::getMaxSizeF() const
{
	return this->maxSizeWorld;
}

const bool TileMap::tileEmpty(const int x, const int y, const int z) const
{
	if (x >= 0 && x < this->maxSize.x &&
		y >= 0 && y < this->maxSize.y &&
		z >= 0 && z <= this->layers)
	{
		return this->map[x][y][z].empty();
	}
}