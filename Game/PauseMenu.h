#pragma once

#include<ctime>
#include<cstdlib>
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<SFML/System.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<vector>
#include<fstream>
#include<sstream>
#include<stack>
#include<map>
#include "GUI.h"

using namespace GUI;

class PauseMenu
{
public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	std::map<std::string, Button*>& getButtons();
	void addButton(const std::string key, float y, const std::wstring text);

	void render(sf::RenderTarget& target);
	void update(const sf::Vector2i& mousePosition);

	const bool isButtonPressed(const std::string key);

private:
	sf::Font& font;
	sf::Text menutext;	

	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;
};

