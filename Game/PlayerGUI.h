#pragma once
#include "Player.h"


class Player;
class sf::RectangleShape;
class sf::VideoMode;

class PlayerGUI
{
private:

	sf::Font font;
	sf::Text hpBarText;
	std::string hpBarStr;
	Player* player;
	sf::RectangleShape hpBarBg;
	sf::RectangleShape hpBarCont;

	sf::VideoMode vm;

	sf::Text xpBarText;
	std::string xpBarStr;
	sf::RectangleShape xpBarBg;
	sf::RectangleShape xpBarCont;
	void InitFont(std::string path);

	sf::Text lvlBarText;
	std::string lvlBarStr;
	sf::RectangleShape lvlBar;

	float hpBarMaxWidth;
	float xpBarMaxWidth;

	void InitHpBar();
	void InitXpBar();
	void InitLevelBar();


public:
	PlayerGUI(Player* player, sf::VideoMode& vmode);
	virtual ~PlayerGUI();

	void update(const float& dt);
	void render(sf::RenderTarget& target);

	void updateHp();
	void renderHp(sf::RenderTarget& target);

	void updateXp();
	void renderXp(sf::RenderTarget& target);

	void updateLVL();
	void renderLVL(sf::RenderTarget& target);
};

