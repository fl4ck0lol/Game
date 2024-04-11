#pragma once


class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();

	float offset_x;
	float offset_y;

	void update();
	void render(sf::RenderTarget& target);
	bool checkCollision(const sf::FloatRect& collision);

private:
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
};

