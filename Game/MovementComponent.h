#pragma once



enum move_states {
	IDLE = 0,
	MOVING,	
	LEFT,
	RIGHT,
	UP,
	DOWN
};

class MovementComponent
{
private:
	float maxVelocity;
	sf::Vector2f Velocity;
	float acceleration;
	float deceleration;
	sf::Sprite& sprite;

public:
	MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration);
	~MovementComponent();

	void Update(const float& dt);
	void Move(const float directionX, const float directionY, const float& dt);

	const float& getMaxVelocity() const;
	const sf::Vector2f getVelocity() const;

	const bool Idle() const;

	const bool getMoveState(const short unsigned movestate) const;
};

