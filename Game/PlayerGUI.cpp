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
	this->hpBar->update(this->player->getAtrComp()->HP, this->player->getAtrComp()->maxHP);
	this->xpBar->update(this->player->getAtrComp()->xp, this->player->getAtrComp()->xpNext);
}

void PlayerGUI::render(sf::RenderTarget& target, sf::Shader* shader, Entity* player)
{
	this->hpBar->render(target, shader, player);
	this->xpBar->render(target, shader, player);
}

void PlayerGUI::InitiBars()
{
	sf::Color* hpcolor = new sf::Color(sf::Color::Red);
	sf::Color* xpcolor = new sf::Color(sf::Color::Blue);
	this->hpBar = new GUI::ProgressBar(30.f, 30.f, 250.f, 30.f, this->player->getAtrComp()->maxHP, hpcolor, &this->font, &this->vm);
	this->xpBar = new GUI::ProgressBar(30.f, 70.f, 250.f, 30.f, this->player->getAtrComp()->xpNext, xpcolor, &this->font, &this->vm);
}
