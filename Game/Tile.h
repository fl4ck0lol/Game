#pragma once
enum Tile_types{DEFAULT = 0, DAMAGING};

class Tile
{
protected:
	sf::RectangleShape tileShape;
	bool colliding;
	short unsigned type;

public:

	Tile();
	Tile(unsigned x, unsigned y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect, bool colliding = false, short unsigned type = Tile_types::DEFAULT);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

	const std::string getAsString() const;

};

