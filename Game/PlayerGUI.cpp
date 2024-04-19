#include "stdafx.h"
#include "PlayerGUI.h"
#include"GUI.h"

PlayerGUI::PlayerGUI(Player* player, sf::Font font, sf::VideoMode& vmode)
{
	this->vm = vmode;
	this->font = font;
	this->player = player;
	
	this->InitiBars();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
}

void PlayerGUI::update(const float& dt)
{
	this->hpBar->update(this->player->getAtrComp()->HP);
	this->xpBar->update(this->player->getAtrComp()->xp);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->hpBar->render(target);
	this->xpBar->render(target);
}

void PlayerGUI::InitiBars()
{
	sf::Color* hpcolor = new sf::Color(sf::Color::Red);
	sf::Color* xpcolor = new sf::Color(sf::Color::Blue);
	this->hpBar = new GUI::ProgressBar(20.f, 20.f, 150.f, 50.f, this->player->getAtrComp()->HP, hpcolor, &this->font, &this->vm);
	this->xpBar = new GUI::ProgressBar(20.f, 80.f, 150.f, 50.f, this->player->getAtrComp()->xp, xpcolor, &this->font, &this->vm);
}
