#include "stdafx.h"
#include "Item.h"

void Item::InitVars()
{

}

Item::Item(unsigned value)
{
	this->InitVars();

	this->value = itemTypes::DEFAULT_ITEM;
	this->type = 0;
}

Item::~Item()
{

}
