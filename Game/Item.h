#pragma once

enum itemTypes{DEFAULT_ITEM = 0, RANGED, MELEE};

class Item
{
private:
	void InitVars();

protected:
	short unsigned type;
	unsigned value;

public:
	Item(unsigned value);
	virtual ~Item();	

	virtual Item* clone() = 0;
};