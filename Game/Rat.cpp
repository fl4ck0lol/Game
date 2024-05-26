#include "stdafx.h"
#include "Rat.h"

class Enemy;

Rat::Rat(sf::Texture& textureSheet, float x, float y, EnemySpawner& enemySpawner, Entity& player) : Enemy(enemySpawner), player(player)
{
	this->InitialiseVariables();
	this->setPosition(x, y);
	this->InitialiseAnimComp(textureSheet);
	this->InitialiseHitboxComp(this->sprite, 45.f, 50.f, -25.f, 30.f);
	this->InitialiseMoveComp(50.f, 1600.f, 1000.f);
	this->InitialiseAttributeComp(1);

	this->InitialiseAnimations();

	this->InitialiseBar();

	this->InitialiseAI();

	this->follow = new AiFollow(*this, player);
}
//201

Rat::~Rat()
{
	delete this->follow;
}

void Rat::update(const float& dt, sf::Vector2f& mousePos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E))
		this->attributeComponent->getXP(20);

	this->movementComponent->Update(dt);

	this->updateAttack(dt);

	this->updateAnimation(dt);

	this->hitboxComponent->update();

	this->healthBar->update(this->attributeComponent->HP, this->attributeComponent->maxHP);
	this->healthBar->updatePosition(this->getPosition().x - 35, this->getPosition().y - 10);

	this->follow->update(dt);

}

void Rat::render(sf::RenderTarget& target, sf::Shader* shader, Entity* player, bool showHitbox)
{
	if (shader)
	{
		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getPlayerCenter());

		target.draw(this->sprite, shader);

		shader->setUniform("hasTexture", true);
		shader->setUniform("lightPos", this->getPlayerCenter());

		this->healthBar->render(target, shader, player);
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

void Rat::InitialiseBar()
{
	sf::Color healthColor = sf::Color::Red;

	this->healthBar = new GUI::ProgressBar(
		this->sprite.getPosition().x - 20, this->sprite.getPosition().y - 20, 50.f, 10.f, this->attributeComponent->HP, &healthColor);
}

void Rat::InitialiseAI()
{
	
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