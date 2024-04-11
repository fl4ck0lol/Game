#include "stdafx.h"
#include "MovementComponent.h"

MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity, float acceleration, float deceleration) 
	: sprite(sprite), maxVelocity(maxVelocity), acceleration(acceleration), deceleration(deceleration)
{

}

MovementComponent::~MovementComponent()
{

}

void MovementComponent::Update(const float& dt)
{
	if (this->Velocity.x > 0.f)
	{
		if (this->Velocity.x > this->maxVelocity)
			this->Velocity.x = maxVelocity;

		this->Velocity.x -= deceleration;
		if (this->Velocity.x < 0.f)
			this->Velocity.x = 0;

	}
	else if (this->Velocity.x < 0.f)
	{
		if (this->Velocity.x < -this->maxVelocity)
			this->Velocity.x = -this->maxVelocity;

		this->Velocity.x += deceleration;
		if (this->Velocity.x > 0.f)
			this->Velocity.x = 0;
	}
	if (this->Velocity.y > 0.f)
	{
		if (this->Velocity.y > this->maxVelocity)
			this->Velocity.y = maxVelocity;

		this->Velocity.y -= deceleration;
		if (this->Velocity.y < 0.f)
			this->Velocity.y = 0;

	}
	else if (this->Velocity.y < 0.f)
	{
		if (this->Velocity.y < -this->maxVelocity)
			this->Velocity.y = -this->maxVelocity;

		this->Velocity.y += deceleration;
		if (this->Velocity.y > 0.f)
			this->Velocity.y = 0;
	}

	this->sprite.move(this->Velocity * dt);
}

void MovementComponent::Move(const float directionX, const float directionY, const float& dt)
{
	this->Velocity.x += this->acceleration * directionX;

	this->Velocity.y += this->acceleration * directionY;

}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

const sf::Vector2f MovementComponent::getVelocity() const
{
	return this->Velocity;
}

const bool MovementComponent::Idle() const
{
	if (this->Velocity.x == 0.f && this->Velocity.y == 0.f)
		return true;
	return false;
}

const bool MovementComponent::getMoveState(const short unsigned movestate) const
{
	switch (movestate) {
	case IDLE:
		if (this->Velocity.x == 0.f && this->Velocity.y == 0.f)
			return true;
		break;
	case MOVING:
		if (this->Velocity.x != 0.f || this->Velocity.y != 0.f)
			return true;
	case LEFT:
		if (this->Velocity.x < 0.f)
			return true;
		break;
	case RIGHT:
		if (this->Velocity.x > 0.f)
			return true;
		break;
	case UP:
		if (this->Velocity.y > 0.f)
			return true;
		break;
	case DOWN:
		if (this->Velocity.y < 0.f)
			return true;
		break;
	default:
		return false;
		break;
	}
	return false;
}
