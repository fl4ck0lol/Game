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

enum button_states{idle_state = 0, hover_state, pressed_state};

class Button
{

private:
	sf::RectangleShape buttonShape;
	sf::Font* font;
	sf::Text Buttontext;

	sf::Color idle;
	sf::Color hover;
	sf::Color pressed;

	sf::Color textIdle;
	sf::Color textHover;
	sf::Color textPressed;

	short unsigned buttonState;

public:
	Button(float x, float y, float width, float height, std::string text,sf::Color textColor,
		sf::Font* font, sf::Color idle, sf::Color hover, sf::Color pressed, unsigned charSize, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor);
	~Button();

	void update(const sf::Vector2f mousePosition);
	void render(sf::RenderTarget& target);

	const bool isPressed() const;
};

