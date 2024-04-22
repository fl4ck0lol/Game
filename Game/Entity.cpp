#include "stdafx.h"
#include "Entity.h"

void Entity::Variables()
{
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
	this->attributeComponent = NULL;
	this->skillComponent = NULL;
}

Entity::Entity()
{
	Variables();
}

Entity::~Entity()
{
	delete this->movementComponent;
	delete this->animationComponent;
	delete this->hitboxComponent;
	delete this->attributeComponent;
	delete this->skillComponent;
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

void Entity::update(const float& dt, sf::Vector2f& mousePos)
{
	
}

void Entity::render(sf::RenderTarget& target, sf::Shader* shader, Entity* entity, const bool showHitbox)
{

}

void Entity::setPosition(const float x,const float y)
{
	if (this->hitboxComponent)
		this->hitboxComponent->setPosition(x, y);
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
	this->hitboxComponent = new HitboxComponent(this->sprite, offset_x, offset_x, width, height);
}

void Entity::InitialiseAttributeComp(const unsigned lvl)
{
	this->attributeComponent = new AttributeComponent(lvl);
}

void Entity::InitialiseSkillComp()
{
	this->skillComponent = new SkillComponent();
}

const sf::Vector2f& Entity::getPosition() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition();
	return this->sprite.getPosition();
}

const sf::Vector2f Entity::getPlayerCenter() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getPosition() + 
			sf::Vector2f(
				this->hitboxComponent->getGlobalBounds().width / 2, 
				this->hitboxComponent->getGlobalBounds().height / 2);
	return this->sprite.getPosition() + 
			sf::Vector2f(
				this->sprite.getGlobalBounds().width / 2, 
				this->sprite.getGlobalBounds().height / 2);;
}

const sf::Vector2i Entity::getGridPos(const int gridSizeI) const
{
	if (this->hitboxComponent)
		return sf::Vector2i(
			static_cast<int>(this->hitboxComponent->getPosition().x) / gridSizeI,
			static_cast<int>(this->hitboxComponent->getPosition().y) / gridSizeI
		);

	return sf::Vector2i(
		static_cast<int>(this->sprite.getPosition().x) / gridSizeI,
		static_cast<int>(this->sprite.getPosition().y) / gridSizeI
	);
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
		return this->hitboxComponent->getGlobalBounds();
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPosBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
		return this->hitboxComponent->getNextPos(this->movementComponent->getVelocity() * dt);
	return sf::FloatRect(-1, -1, -1, -1);
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

const float Entity::getDistance(const Entity* point) const
{
	return sqrt(pow(this->getPlayerCenter().x - point->getPlayerCenter().x, 2) + pow(this->getPlayerCenter().y - point->getPlayerCenter().y, 2));
}
