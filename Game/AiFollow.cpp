#include "stdafx.h"
#include "AiFollow.h"

AiFollow::AiFollow(Entity* self, Entity& entity) : AiOption(self, entity)
{

}

AiFollow::~AiFollow()
{
}

void AiFollow::update(const float& dt)
{
	sf::Vector2f moveVec;
	moveVec.x = self.getPosition().x - entity.getPosition().x;
	moveVec.y = self.getPosition().y - entity.getPosition().y;	

	float vecLength = sqrt(pow(moveVec.x, 2) + pow(moveVec.y, 2));

	moveVec /= vecLength;

	if (self.getPosition().x != entity.getPosition().x)
	{
		self.move(moveVec.x, moveVec.y, dt);
	}
}


