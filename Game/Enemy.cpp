#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy() 
{
	this->InitialiseVariables();
	this->InitialiseAnimations();
}

Enemy::~Enemy()
{

}


AttributeComponent* Enemy::getAtrComp()
{
	return this->attributeComponent;
}

void Enemy::loseHP(const int dmg)
{
	if (this->attributeComponent)
	{
		this->attributeComponent->loseHP(dmg);	
	}
}

void Enemy::InitialiseVariables()
{
	this->xp = 10;
	this->attacking = false;
}

void Enemy::InitialiseAnimations()
{

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


void Enemy::loseHp(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

const AttributeComponent* Enemy::GetAtrComp() const
{
	if (this->attributeComponent)
		return this->attributeComponent;
	else
		return nullptr;
}

const bool Enemy::isDead() const
{
	if (this->attributeComponent)
	{
		return this->attributeComponent->isDead();
	}

	return false;
}

const unsigned& Enemy::giveXp() const
{
	return this->xp;
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
