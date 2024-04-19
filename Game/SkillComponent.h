#pragma once
class Skill;

enum skills_enum {HEALTH = 0, ATTACK, ACCURACY, STRENGTH, ENDURANCE, VITALITY};

class SkillComponent
{
public:
	SkillComponent();
	virtual ~SkillComponent();

	const int getSkill(const int skill) const;
	const void gainXp(const int skill, const int xp);


private:
	class Skill {
	private:
		int type;
		int lvl;
		int xp;
		int nextXp;
		int lvlCap;

	public:

		Skill(const int type)
		{
			this->type = type;
			this->lvl = 1;
			this->lvlCap = 10;
			this->xp = 0;
			this->nextXp = 50;
		}

		virtual ~Skill()
		{

		}

		void updateLvl(const bool up = true) 
		{
			if (up)
			{

				if (this->lvl < this->lvlCap)
				{
					while (this->xp >= this->nextXp)
					{
						if (++this->lvl < this->lvlCap)
						{
							++this->lvl;
							this->nextXp = this->lvl * 50;
						}
					}
				}

			}
			else
			{
				if (this->lvl > 0)
				{
					while (this->xp < 0)
					{
						if (this->lvl > 0)
						{
							--this->lvl;
							this->nextXp = this->lvl * 50;
						}
					}
				}
			}
		}

		inline const int& getType() const { return this->type; }
		inline const int& getLvl() const { return this->lvl; }
		inline const int& getXp() const { return this->xp; }
		inline const int& getNextXp() const { return this->nextXp; }

		void gainXp(const int xp) 
		{ 
			this->xp += xp;
			this->updateLvl();
		}

		void loseXp(const int xp)
		{
			this->xp -= xp;
		}

		void setLvl(const int lvl) { this->lvl = lvl; }
		void setLvlCap(const int lvlCap) { this->lvlCap = lvlCap; }

	};

	std::vector<Skill> skills;
};

