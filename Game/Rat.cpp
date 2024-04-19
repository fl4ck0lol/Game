#include "stdafx.h"
#include "Rat.h"

Rat::Rat(sf::Texture& textureSheet, float x, float y) : Enemy()
{

}

Rat::~Rat()
{
}

void Rat::update(const float& dt, sf::Vector2f& mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->attributeComponent->getXP(20);

	this->movementComponent->Update(dt);

	this->updateAttack(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, const bool showHitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getPlayerCenter());

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getPlayerCenter());

	}
	else
	{
		target.draw(this->sprite);
	}

	if (showHitbox)
		this->hitboxComponent->render(target);
}

AttributeComponent* Rat::getAtrComp()
{
	return this->attributeComponent;
}

void Rat::InitialiseVariables()
{

}

void Rat::InitialiseAnimations()
{
	this->animationComponent->addAnimation("IDLE", 25.f, 0, 0, 3, 0, 60, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 60, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 11.f, 0, 2, 3, 2, 60, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 0, 3, 3, 3, 60, 64);
	this->animationComponent->addAnimation("WALK_UP", 11.f, 0, 4, 3, 4, 60, 64);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 60, 64);


}

void Rat::updateAttack(const float& dt)
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

void Rat::updateAnimation(const float& dt)
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

void Rat::loseHP(const int hp)
{
	this->attributeComponent->loseHP(hp);
}

void Rat::loseXP(const int xp)
{
	this->attributeComponent->loseXP(xp);
}

void Rat::gainHP(const int hp)
{
	this->attributeComponent->getHP(hp);
}

void Rat::gainXP(const int xp)
{
	this->attributeComponent->getXP(xp);
}
