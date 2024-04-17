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

	this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
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

	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target, sf::Shader* shader, const bool showHitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getPlayerCenter());

		target.draw(this->sprite, shader);
	}
	else
		target.draw(this->sprite);

	if(showHitbox)
		this->hitboxComponent->render(target);
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
	if (this->attacking)
	{

	}
	if (this->movementComponent->getMoveState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getMoveState(LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getMoveState(DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
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
