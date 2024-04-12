#include "stdafx.h"
#include "PauseMenu.h"
using namespace GUI;

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font) : font(font)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(window.getSize().x / 3.f), static_cast<float>(window.getSize().y)));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setPosition(static_cast<float>(window.getSize().x) / 2.f - this->container.getSize().x / 2.f, 0.f);

	this->menutext.setCharacterSize(100);
	this->menutext.setFont(this->font);
	this->menutext.setFillColor(sf::Color(255, 255, 255, 255));
	this->menutext.setString(L"Пауза");
	this->menutext.setPosition(this->container.getPosition().x + (this->container.getSize().x - this->menutext.getGlobalBounds().width) / 2.f, 55.f);

}

PauseMenu::~PauseMenu()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

void PauseMenu::addButton(const std::string key, float y, const std::wstring text)
{
	float width = 150.f;
	float height = 50.f;
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new Button(x, y, width, height, text, sf::Color(52, 61, 70, 0), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(192, 197, 206, 250), sf::Color(101, 115, 126, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);

	for (auto& i : this->buttons)
	{
		i.second->render(target);
	}

	target.draw(this->menutext);
}

void PauseMenu::update(const sf::Vector2f& mousePosition)
{
	for (auto& i : buttons)
	{
		i.second->update(mousePosition);
	}
}

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}
