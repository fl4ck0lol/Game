	#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"


class Entity
{
private:
	void Variables();
	

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponenet;

public:
	Entity();
	virtual ~Entity();


	void setTexture(sf::Texture& texture);

	virtual void move(const float x, const float y, const float& dt);
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
	virtual void setPosition(const float x, const float y);

	void InitialiseAnimComp(sf::Texture& textureSheet);
	void InitialiseMoveComp(const float MaxVelocity, const float acceleration, const float deceleration);
	void InitialiseHitboxComp(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);

	virtual const sf::Vector2f& getPosition();
	virtual const sf::Vector2u getGridPos(const unsigned gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;

	virtual void stopVelocityX();
	virtual void stopVelocityY();
};
