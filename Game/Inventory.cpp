#include "stdafx.h"
#include "Inventory.h"

Inventory::Inventory(unsigned capacity)
{
	this->maxNums = capacity;
	this->numOfItems = 0;
	this->Initialise();
}

Inventory::~Inventory()
{
	this->freeMemory();
}

void Inventory::clear()
{
	for (size_t i = 0; i < this->numOfItems; i++)
	{
		delete this->itemArray[i];
	}
	this->numOfItems = 0;
	this->nullify();
}

const unsigned& Inventory::Size()
{
	return this->numOfItems;
}

const unsigned& Inventory::getMaxSize()
{
	return this->maxNums;
}

const bool Inventory::isEmpty() const
{
	return this->numOfItems == 0;
}

const bool Inventory::Add(Item* item)
{
	if (this->numOfItems < this->maxNums)
	{
		this->itemArray[this->numOfItems++] = item->clone();
		return true;
	}

	return false;
}

const bool Inventory::Remove(const unsigned index)
{
	if (this->numOfItems > 0)
	{
		if (index < 0 || index >= this->maxNums)
			return false;

		delete this->itemArray[index];
		this->itemArray[index] = nullptr;

		return true;
	}
	return false;
}

const bool Inventory::saveToFile(std::string filename)
{
	return false;
}

const bool Inventory::loadToFile(std::string filename)
{
	return false;
}

void Inventory::Initialise()
{
	this->numOfItems = 0;
	this->itemArray = new Item * [this->maxNums];

	this->nullify();

	
}

void Inventory::expand()
{
}

void Inventory::nullify(const unsigned from)
{
	for (size_t i = from; i < this->maxNums; i++)
	{
		this->itemArray[i] = nullptr;
	}
}

void Inventory::freeMemory()
{
	for (size_t i = 0; i < this->numOfItems; i++)
	{
		delete this->itemArray[i];
	}

	delete[] this->itemArray;
}
