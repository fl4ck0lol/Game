#include "stdafx.h"
#include "PauseMenu.h"
using namespace GUI;

PauseMenu::PauseMenu(sf::VideoMode& vm, sf::Font& font) : font(font)
{
	this->background.setSize(sf::Vector2f(static_cast<float>(vm.width), static_cast<float>(vm.height)));
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	this->container.setSize(sf::Vector2f(static_cast<float>(vm.width / 3.f), static_cast<float>(vm.height)));

	this->container.setFillColor(sf::Color(20, 20, 20, 200));

	this->container.setPosition(static_cast<float>(vm.width) / 2.f - this->container.getSize().x / 2.f, 0.f);

	this->menutext.setCharacterSize(GUI::calcCharSize(vm) + 50);
	this->menutext.setFont(this->font);
	this->menutext.setFillColor(sf::Color(255, 255, 255, 255));
	this->menutext.setString(L"Пауза");
	this->menutext.setPosition(this->container.getPosition().x + (this->container.getSize().x - this->menutext.getGlobalBounds().width) / 2.f, 
		GUI::PixelPercentY(5, vm));

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

void PauseMenu::addButton(const std::string key, const float y, const float width, const float height, const unsigned charSize, const std::wstring text)
{
	float x = this->container.getPosition().x + this->container.getSize().x / 2.f - width / 2.f;

	this->buttons[key] = new Button(x, y, width, height, text, sf::Color(52, 61, 70, 0), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), charSize,
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

void PauseMenu::update(const sf::Vector2i& mousePosition)
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
