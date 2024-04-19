#include "stdafx.h"
#include "SkillComponent.h"

SkillComponent::SkillComponent()
{
	this->skills.push_back(Skill(skills_enum::HEALTH));
	this->skills.push_back(Skill(skills_enum::ATTACK));
	this->skills.push_back(Skill(skills_enum::ACCURACY));
	this->skills.push_back(Skill(skills_enum::STRENGTH));
	this->skills.push_back(Skill(skills_enum::VITALITY));
	this->skills.push_back(Skill(skills_enum::ENDURANCE));
}

SkillComponent::~SkillComponent()
{
}

const int SkillComponent::getSkill(const int skill) const
{
	if (skill < 0 || skill >= this->skills.size() || this->skills.empty())
		throw("no skill: " + skill); 
	else
		return this->skills[skill].getLvl();
}

const void SkillComponent::gainXp(const int skill, const int xp)
{
	if (skill < 0 || skill >= this->skills.size() || this->skills.empty())
		throw("no skill: " + skill);
	else
	{
		this->skills[skill].gainXp(xp);
	}
}
