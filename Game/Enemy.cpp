#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() 
{

	
}

Enemy::~Enemy()
{

}


AttributeComponent* Enemy::getAtrComp()
{
	return this->attributeComponent;
}

void Enemy::InitialiseVariables()
{
	
}

void Enemy::InitialiseAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);

}

void Enemy::updateAttack(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	{
		this->attacking = true;

	}
	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;

	}
}

void Enemy::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Enemy::loseXP(const int xp)
{
	this->attributeComponent->loseXP(xp);
}

void Enemy::gainHP(const int hp)
{
	this->attributeComponent->getHP(hp);
}

void Enemy::gainXP(const int xp)
{
	this->attributeComponent->getXP(xp);
}
