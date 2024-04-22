#pragma once
#include "Player.h"
#include"GUI.h"


class Player;
class sf::RectangleShape;
class sf::VideoMode;

class PlayerGUI
{
private:
	sf::Font font;
	Player* player;
	GUI::ProgressBar* hpBar;
	GUI::ProgressBar* xpBar;

	sf::VideoMode vm;

	void InitiBars();

public:

	PlayerGUI(Player* player, sf::Font, sf::VideoMode& vmode);
	~PlayerGUI();

	void update(const float& dt);
	void render(sf::RenderTarget& target, sf::Shader* shader = nullptr, Entity* player = nullptr);
};

