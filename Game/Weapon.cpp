#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(unsigned value, std::string file) : Item(value)
{
	this->initVars();
	this->weaponTexture.loadFromFile(file);
	this->weaponSprite.setTexture(this->weaponTexture);
	this->initCD();
}

Weapon::Weapon(unsigned minDmg, unsigned maxDmg, unsigned range, unsigned value, std::string file) : Item(value)
{
	this->initVars();
	this->weaponTexture.loadFromFile(file);
	this->weaponSprite.setTexture(this->weaponTexture);
	this->initCD();
	this->minDmg = minDmg;
	this->maxDmg = maxDmg;
	this->range = range;
}

Weapon::~Weapon()
{
}

const unsigned& Weapon::getRange() const
{
	return this->range;
}

const unsigned& Weapon::getMinDmg() const
{
	return this->minDmg;
}

const unsigned& Weapon::getDmg() const
{
	return rand() % ((this->maxDmg - this->minDmg) + 1) + (this->minDmg);
}

const unsigned& Weapon::getMaxDmg() const
{
	return this->maxDmg;
}

const bool Weapon::getAttackTimer()
{
	if (this->attackTimer.getElapsedTime().asMilliseconds() >= this->attackTimerMax)
	{
		this->attackTimer.restart();
		return true;
	}
	return false;
}

void Weapon::initVars()
{
	this->range = 50;
	this->minDmg = 1;
	this->maxDmg = 2;

	this->attackTimer.restart();
	this->attackTimerMax = 500;
}

void Weapon::initCD()
{
	this->CD = 0.f;
	this->maxCD = 10.f;
	this->CDiteration = 1.f;
}

