#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Texture& textureSheet, float x, float y)
{
	this->InitialiseVariables();

	this->setPosition(x, y);

	this->InitialiseMoveComp(200.f, 15.f, 5.f);
	this->InitialiseAnimComp(textureSheet);
	this->InitialiseHitboxComp(this->sprite, 10.f, 5.f, 40.f, 50.f);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4, 5, 4, 64, 64);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 3, 7, 3, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 8, 7, 8, 64, 64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{

	this->movementComponent->Update(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->attacking = true;

	}
	if (this->attacking)
	{
		if(this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;

	}

	if (this->movementComponent->getMoveState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getMoveState(RIGHT))
	{
		this->sprite.setOrigin(0.f, 0.f);
		this->sprite.setScale(1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(LEFT))
	{
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width , 0.f);
		this->sprite.setScale(-1.f, 1.f);
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}

	this->hitboxComponenet->update();
}

void Player::InitialiseVariables()
{
	attacking = false;
}

