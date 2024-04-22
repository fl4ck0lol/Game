#pragma once

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeComponent.h"
#include "SkillComponent.h"

class Entity
{
private:
	void Variables();

protected:
	sf::Sprite sprite;

	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	HitboxComponent* hitboxComponent;
	AttributeComponent* attributeComponent;
	SkillComponent* skillComponent;

public:
	Entity();
	virtual ~Entity();


	void setTexture(sf::Texture& texture);

	virtual void move(const float x, const float y, const float& dt);
	virtual void update(const float& dt, sf::Vector2f& mousePos) = 0;
	virtual void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, Entity* entity = nullptr, const bool showHitbox = false) = 0;
	virtual void setPosition(const float x, const float y);

	void InitialiseAnimComp(sf::Texture& textureSheet);
	void InitialiseMoveComp(const float MaxVelocity, const float acceleration, const float deceleration);
	void InitialiseHitboxComp(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height);
	void InitialiseAttributeComp(const unsigned lvl);
	void InitialiseSkillComp();

	virtual const sf::Vector2f& getPosition() const;
	virtual const sf::Vector2f getPlayerCenter() const;
	virtual const sf::Vector2i getGridPos(const int gridSizei) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPosBounds(const float& dt) const;


	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual const float getDistance(const Entity* point) const;

};
