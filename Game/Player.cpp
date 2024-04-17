#include "stdafx.h"
#include "Player.h"

Player::Player(sf::Texture& textureSheet, float x, float y)
{
	this->InitialiseVariables();

	this->setPosition(x, y);

	this->InitialiseMoveComp(350.f, 1500.f, 500.f);
	this->InitialiseAnimComp(textureSheet);
	this->InitialiseHitboxComp(this->sprite, 10.f, 5.f, 40.f, 50.f);
	this->InitialiseAttributeComp(1);

	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4, 5, 4, 64, 64);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 3, 7, 3, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 7.f, 0, 8, 7, 8, 64, 64);
}

Player::~Player()
{
}

void Player::update(const float& dt)
{
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->attributeComponent->getXp(20);

	this->movementComponent->Update(dt);

	this->updateAttack(dt);

	this->updateAnimation(dt);

	this->hitboxComponenet->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponenet->render(target);
}

AttributeComponent* Player::getAtrComp()
{
	return this->attributeComponent;
}

void Player::InitialiseVariables()
{
	attacking = false;
}

void Player::updateAttack(const float& dt)
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

void Player::updateAnimation(const float& dt)
{
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
		this->sprite.setOrigin(this->sprite.getGlobalBounds().width, 0.f);
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
}

void Player::loseHP(const int hp)
{
	this->attributeComponent->HP -= hp;
	if (this->attributeComponent->HP < 0)
		this->attributeComponent->HP = 0;
}

void Player::loseXP(const int xp)
{
	this->attributeComponent->xp -= xp;
	if (this->attributeComponent->xp < 0)
		this->attributeComponent->xp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->HP += hp;
	if (this->attributeComponent->HP > this->attributeComponent->maxHP)
		this->attributeComponent->HP = this->attributeComponent->maxHP;
}

void Player::gainXP(const int xp)
{
	this->attributeComponent->getXp(xp);
}
