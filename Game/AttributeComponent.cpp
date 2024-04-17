#include "stdafx.h"
#include "AttributeComponent.h"

AttributeComponent::AttributeComponent(int lvl)
{
	this->lvl = lvl;
	this->xp = 0;
	this->xpNext = (50 * pow(this->lvl, 3) - 150 * pow(this->lvl, 2) + (UINT64)400 * this->lvl) / 3;
	this->atrPoints = 2;

	this->vitality = 1;
	this->strength = 1;
	this->intelligence = 1;
	this->agility = 1;
	this->dexterity = 1;

	this->updateLVL();
	this->updateStats(true);
}

AttributeComponent::~AttributeComponent()
{
}

void AttributeComponent::updateStats(const bool reset)
{
	this->maxHP = this->vitality * 5 + this->vitality + this->strength / 2 + this->intelligence / 5;
	this->minDMG = this->strength * 2 + this->strength / 4 + this->intelligence / 5;
	this->maxDMG = this->strength * 2 + this->strength / 2 + this->intelligence / 5;
	this->accuracy = this->dexterity * 4 + this->dexterity / 3 + this->intelligence / 5;
	this->def = this->agility * 2 + this->agility / 4 + this->intelligence / 5;
	this->luck = intelligence * 2 + this->intelligence / 5;

	if(reset)
		this->HP = this->maxHP;
}

void AttributeComponent::updateLVL()
{
	while(this->xp >= this->xpNext)
	{
		++this->lvl;
		this->xp -= this->xpNext;
		this->xpNext = (50 * pow(this->lvl, 3) - 150 * pow(this->lvl, 2) + (UINT64)400 * this->lvl) / 3;
		++this->atrPoints;
	}
}

void AttributeComponent::update()
{
	this->updateLVL();
}

void AttributeComponent::getXp(const int xp)
{
	this->xp += xp;

	this->updateLVL();
}