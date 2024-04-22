#pragma once
#include "Item.h"


class Inventory
{
public:
	Inventory(unsigned capacity);
	virtual ~Inventory();

	void clear();

	const unsigned& Size();
	const unsigned& getMaxSize();

	const bool isEmpty() const;

	const bool Add(Item* item);
	const bool Remove(const unsigned index);

	const bool saveToFile(std::string filename);
	const bool loadToFile(std::string filename);

private:
	Item** itemArray;
	unsigned numOfItems;
	unsigned maxNums;

	void Initialise();
	void expand();
	void nullify(const unsigned from = 0);

	void freeMemory();
};

