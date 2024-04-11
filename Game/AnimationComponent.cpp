#include "stdafx.h"
#include "AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet)
	: sprite(sprite), texture(textureSheet), lastAnimation(NULL), prioAnimation(NULL)
{

}

AnimationComponent::~AnimationComponent()
{
	for (auto& i : this->animations)
	{
		delete i.second;
	}
}

void AnimationComponent::addAnimation(const std::string key, float animationTimer,
	int start_frameX, int start_frameY, int framesX, int framesY, int width, int height)
{
	this->animations[key] = new Animation(this->sprite, this->texture, animationTimer, start_frameX, start_frameY, framesX, framesY, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool prio)
{
	
	if (this->prioAnimation)
	{
		if (this->prioAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];

				}
			}

			if (this->animations[key]->play(dt))
			{
				this->prioAnimation = NULL;
			}
		}
			
	}
	else
	{
		if (prio)
		{
			this->prioAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];

			}
		}
		this->animations[key]->play(dt);

	}
	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool prio)
{
	if (this->prioAnimation)
	{
		if (this->prioAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
					this->lastAnimation = this->animations[key];
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];

				}
			}

			if (this->animations[key]->play(dt))
			{
				this->prioAnimation = NULL;
			}
		}

	}
	else
	{
		if (prio)
		{
			this->prioAnimation = this->animations[key];
		}
		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
				this->lastAnimation = this->animations[key];
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];

			}
		}
		this->animations[key]->play(dt, abs(modifier / modifier_max));

	}
	return this->animations[key]->isDone();
}
const bool& AnimationComponent::isDone(const std::string key) 
{
		return this->animations[key]->isDone();
}
