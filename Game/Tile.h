#pragma once
class Tile
{
protected:
	sf::RectangleShape tileShape;


public:

	Tile();
	Tile(float x, float y, float gridSizeF, const sf::Texture* texture, const sf::IntRect& rect);
	virtual ~Tile();

	void update();
	void render(sf::RenderTarget& target);

};

