#pragma once

class AnimationComponent
{
private:
	sf::Sprite& sprite;
	sf::Texture& texture;
	
	class Animation 
	{
	public:

		sf::Sprite& sprite;

		sf::Texture textureSheet;
		float animationTimer;
		bool done;
		float timer;
		sf::IntRect startrect;
		sf::IntRect endrect;
		sf::IntRect currentrect;
		int width;
		int height;
		Animation(sf::Sprite& sprite, sf::Texture& textureSheet, float animationTimer, int start_frameX, int start_frameY, int framesX, int framesY, int width, int height)
			: sprite(sprite), textureSheet(textureSheet), animationTimer(animationTimer), width(width), height(height), done(false), timer(0.f)
		{
			this->startrect = sf::IntRect(start_frameX * width, start_frameY * height, width, height);
			this->endrect = sf::IntRect(framesX * width, framesY * height, width, height);
			this->currentrect = this->startrect;
			this->sprite.setTexture(this->textureSheet, true);
			this->sprite.setTextureRect(this->startrect);

		}

		const bool& play(const float& dt)
		{
			this->done = false;
			this->timer += 100.f * dt;
			if (this->timer >= animationTimer)
			{
				this->timer = 0.f;

				if (this->currentrect != this->endrect)
				{
					this->currentrect.left += this->width;
				}
				else
				{
					this->currentrect.left = this->startrect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentrect);
			}
			return this->done;
		}

		const bool& play(const float& dt, float mod_percentage)
		{
			this->done = false;
			if (mod_percentage < 0.5f)
				mod_percentage = 0.5;
			this->timer += mod_percentage * 100.f * dt;
			if (this->timer >= animationTimer)
			{
				this->timer = 0.f;

				if (this->currentrect != this->endrect)
				{
					this->currentrect.left += this->width;
				}
				else
				{
					this->currentrect.left = this->startrect.left;
					this->done = true;
				}

				this->sprite.setTextureRect(this->currentrect);
			}
			return this->done;	
		}

		void reset()
		{
			this->timer = this->animationTimer;
			this->currentrect = this->startrect;
		}

		const bool& isDone() const
		{
			return this->done;
		}

	};

	std::map<std::string, Animation*> animations;

	Animation* lastAnimation;
	Animation* prioAnimation;


public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& textureSheet);
	virtual ~AnimationComponent();

	void addAnimation(const std::string key, float animationTimer,
		int start_frameX, int start_frameY, int framesX, int framesY, int width, int height);

	const bool& play(const std::string key, const float& dt, const bool prio = false);

	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool prio = false);

	const bool& isDone(const std::string key);
};

