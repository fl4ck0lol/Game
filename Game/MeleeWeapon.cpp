#include "stdafx.h"
#include "MeleeWeapon.h"

MeleeWeapon::MeleeWeapon(unsigned minDmg, unsigned maxDmg, unsigned range, unsigned value, std::string file) : Weapon(minDmg, maxDmg, range, value, file)
{
	this->type = itemTypes::MELEE;
}

MeleeWeapon::~MeleeWeapon()
{
}
