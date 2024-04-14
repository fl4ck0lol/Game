#pragma once


class HitboxComponent
{
public:
	HitboxComponent(sf::Sprite& sprite, float offset_x, float offset_y, float width, float height);
	virtual ~HitboxComponent();
	void update();
	void render(sf::RenderTarget& target);
	bool checkCollision(const sf::FloatRect& collision);

	const sf::Vector2f& getPosition() const;
	void setPosition(const sf::Vector2f& position);
	void setPosition(const float x, const float y);

	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPos(const sf::Vector2f& velocity);

private:

	float offset_x;
	float offset_y;

	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
};

