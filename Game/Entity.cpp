#include "stdafx.h"
#include "Entity.h"

void Entity::Variables()
{
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->hitboxComponenet = NULL;
}

Entity::Entity()
{
	Variables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponenet;
}

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::move(const float directionX, const float directionY, const float& dt)
{
	if (this->movementComponent)
		this->movementComponent->Move(directionX, directionY, dt);		
}

void Entity::update(const float& dt)
{
	
}

void Entity::render(sf::RenderTarget& target)
{

}

void Entity::setPosition(const float x,const float y)
{
	if (this->hitboxComponenet)
		this->hitboxComponenet->setPosition(x, y);
	else
		this->sprite.setPosition(x, y);
}

void Entity::InitialiseAnimComp(sf::Texture& textureSheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, textureSheet);
}

void Entity::InitialiseMoveComp(const float MaxVelocity, const float acceleration, const float deceleration)
{

	this->movementComponent = new MovementComponent(this->sprite, MaxVelocity, acceleration, deceleration);
}

void Entity::InitialiseHitboxComp(sf::Sprite& sprite, const float offset_x, const float offset_y, const float width, const float height)
{
	this->hitboxComponenet = new HitboxComponent(this->sprite, offset_x, offset_x, width, height);
}

const sf::Vector2f& Entity::getPosition()
{
	if (this->hitboxComponenet)
		return this->hitboxComponenet->getPosition();
	return this->sprite.getPosition();
}

const sf::Vector2u Entity::getGridPos(const unsigned gridSizeU) const
{
	if (this->hitboxComponenet)
		return sf::Vector2u(
			static_cast<unsigned>(this->hitboxComponenet->getPosition().x / gridSizeU), 
			static_cast<unsigned>(this->hitboxComponenet->getPosition().y / gridSizeU));

	return sf::Vector2u(
		static_cast<unsigned>(this->sprite.getPosition().x / gridSizeU),
		static_cast<unsigned>(this->sprite.getPosition().y / gridSizeU));
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponenet)
		return this->hitboxComponenet->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

void Entity::stopVelocityX()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityX();
}

void Entity::stopVelocityY()
{
	if (this->movementComponent)
		this->movementComponent->stopVelocityY();
}

