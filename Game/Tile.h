#pragma once
enum Tile_types{DEFAULT = 0, DAMAGING};

class Tile
{
protected:
	sf::RectangleShape tileShape;
	bool collision;
	short unsigned type;

public:

	Tile();
	Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool collision = false, short unsigned type = Tile_types::DEFAULT);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

	const std::string getAsString() const;

	const sf::Vector2f& getPosition() const;

	const bool& getCollision() const;

	const bool intersects(const sf::FloatRect bounds) const;
};

