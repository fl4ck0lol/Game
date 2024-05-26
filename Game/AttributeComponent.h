#pragma once
class AttributeComponent
{
private:

protected:

public:
	AttributeComponent(int level);
	virtual ~AttributeComponent();

	bool reset;

	int lvl;
	int xp;
	int xpNext;
	int statPoints;
	int atrPoints;

	int strength;
	int vitality;
	int agility;
	int intelligence;
	int dexterity;

	int HP;
	int maxHP;
	int DMG;
	int maxDMG;
	int minDMG;
	int accuracy;
	int def;
	int luck;

	void updateStats(const bool reset);
	void updateLVL();
	void update();

	void loseHP(const int hp);
	void loseXP(const int xp);
	void getHP(const int hp);
	void getXP(const int xp);

	const bool isDead() const;

	const int returnHp() const;
};

