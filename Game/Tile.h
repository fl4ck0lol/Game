#pragma once
enum Tile_types{DEFAULT = 0, DAMAGING, DOODAD, ENEMYSPAWNER};

class Tile
{
protected:
	sf::Sprite tileShape;
	bool collision;
	short unsigned type;

public:

	Tile();
	Tile(int x, int y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision = false, short type = Tile_types::DEFAULT, short enemyType = 0);
	virtual ~Tile();

	virtual void update();
	void render(sf::RenderTarget& target, const sf::Vector2f playerPos = sf::Vector2f(), sf::Shader* shader = nullptr);

	const std::string getAsString() const;

	const sf::Vector2f& getPosition() const;

	const sf::FloatRect getGlobalBounds();

	const bool& getCollision() const;

	const bool intersects(const sf::FloatRect bounds) const;

	const short& getType() const;

	const bool SpawnerType() const;
};

