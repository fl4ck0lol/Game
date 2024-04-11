#include "Button.h"


Button::Button(float x, float y, float width, float height, std::string text, sf::Color textColor, sf::Font* font,
	sf::Color idle, sf::Color hover, sf::Color pressed, unsigned charSize, sf::Color idleColor, sf::Color hoverColor, sf::Color pressedColor)
{
	this->buttonShape.setPosition(sf::Vector2f(x, y));
	this->buttonShape.setSize(sf::Vector2f(width, height));
	this->font = font;
	this->Buttontext.setFont(*this->font);
	this->Buttontext.setString(text);
	this->Buttontext.setFillColor(textIdle);
	this->Buttontext.setCharacterSize(charSize);
	this->idle = idle;
	this->hover = hover;
	this->pressed = pressed;
	this->buttonShape.setFillColor(idle);
	this->Buttontext.setPosition(
		this->buttonShape.getPosition().x + (this->buttonShape.getGlobalBounds().width / 2.f) - this->Buttontext.getGlobalBounds().width / 2.f,
		this->buttonShape.getPosition().y + (this->buttonShape.getGlobalBounds().height / 2.f) - this->Buttontext.getGlobalBounds().height / 2.f);
	this->textIdle = idleColor;
	this->textHover = hoverColor;
	this->textPressed = pressedColor;
	this->buttonState = idle_state;
}

Button::~Button()
{

}

void Button::update(const sf::Vector2f mousePosition)
{
	this->buttonState = idle_state;
	if (this->buttonShape.getGlobalBounds().contains(mousePosition))
	{
		this->buttonState = hover_state;

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = pressed_state;
		}
	}

	switch (this->buttonState)
	{
	case idle_state:
		this->buttonShape.setFillColor(this->idle);
		this->Buttontext.setFillColor(this->textIdle);
		break;
	case hover_state:
		this->buttonShape.setFillColor(this->hover);
		this->Buttontext.setFillColor(this->textHover);
		break;
	case pressed_state:
		this->buttonShape.setFillColor(this->pressed);
		this->Buttontext.setFillColor(this->textPressed);
		break;
	default:
		this->buttonShape.setFillColor(sf::Color::Red);
		break;
	}
		
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->buttonShape);
	target.draw(this->Buttontext);
}

const bool Button::isPressed() const
{
	if (this->buttonState == pressed_state)
		return true;


	return false;
}
