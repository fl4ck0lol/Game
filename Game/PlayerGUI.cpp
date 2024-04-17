#include "stdafx.h"
#include "PlayerGUI.h"
#include"GUI.h"

void PlayerGUI::InitFont(std::string path)
{
	this->font.loadFromFile(path);
}

void PlayerGUI::InitHpBar()
{
	float W, H;
	W = GUI::PixelPercentX(15.15, this->vm);
	H = GUI::PixelPercentY(5.56, this->vm);
	this->hpBarMaxWidth = W;
	this->hpBarBg.setSize(sf::Vector2f(W, H));
	this->hpBarBg.setFillColor(sf::Color(0, 0, 0, 200));
	this->hpBarBg.setPosition(GUI::PixelPercentX(2.02, this->vm), GUI::PixelPercentY(1.85, this->vm));
	this->hpBarBg.setOutlineThickness(1.f);
	this->hpBarBg.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->hpBarCont.setSize(sf::Vector2f(W, H));
	this->hpBarCont.setFillColor(sf::Color(210, 4, 45, 200));
	this->hpBarCont.setPosition(this->hpBarBg.getPosition());

	this->hpBarText.setFont(this->font);
	this->hpBarText.setCharacterSize(GUI::calcCharSize(vm) - 10);
}

void PlayerGUI::InitXpBar()
{
	float W, H;
	W = GUI::PixelPercentX(15.15, this->vm);
	H = GUI::PixelPercentY(5.56, this->vm);
	this->xpBarMaxWidth = W;
	this->xpBarBg.setSize(sf::Vector2f(W, H));
	this->xpBarBg.setFillColor(sf::Color(0, 0, 0, 200));
	this->xpBarBg.setPosition(GUI::PixelPercentX(2.02, this->vm), GUI::PixelPercentY(8.33, this->vm));
	this->xpBarBg.setOutlineThickness(1.f);
	this->xpBarBg.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->xpBarCont.setSize(sf::Vector2f(W, H));
	this->xpBarCont.setFillColor(sf::Color(0, 150, 255, 200));
	this->xpBarCont.setPosition(this->xpBarBg.getPosition());

	this->xpBarText.setFont(this->font);
	this->xpBarText.setCharacterSize(GUI::calcCharSize(this->vm) - 10);
}

void PlayerGUI::InitLevelBar()
{
	float W, H;
	W = GUI::PixelPercentY(5.56, this->vm);
	H = GUI::PixelPercentY(5.56, this->vm);

	this->lvlBar.setSize(sf::Vector2f(W, H));
	this->lvlBar.setFillColor(sf::Color(0, 0, 0, 200));
	this->lvlBar.setPosition(GUI::PixelPercentX(17.67, this->vm), GUI::PixelPercentY(8.33, this->vm));
	this->lvlBar.setOutlineThickness(1.f);
	this->lvlBar.setOutlineColor(sf::Color(255, 255, 255, 200));


	this->lvlBarText.setFont(this->font);
	this->lvlBarText.setCharacterSize(GUI::calcCharSize(this->vm) - 10);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vmode) : vm(vmode)
{
	this->player = player;
	this->InitFont("Fonts/Roboto-thin.ttf");
	this->InitHpBar();
	this->InitXpBar();
	this->InitLevelBar();
}

PlayerGUI::~PlayerGUI()
{
}

void PlayerGUI::update(const float& dt)
{
	this->updateHp();
	this->updateXp();
	this->updateLVL();
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderHp(target);	
	this->renderXp(target);
	this->renderLVL(target);
}

void PlayerGUI::updateHp()
{
	float percent = static_cast<float>(this->player->getAtrComp()->HP )
		/ static_cast<float>(this->player->getAtrComp()->maxHP);

	this->hpBarCont.setSize(sf::Vector2f(static_cast<float>(std::floor(this->hpBarMaxWidth * percent)), this->hpBarCont.getSize().y));
	this->hpBarStr = std::to_string(this->player->getAtrComp()->HP) + " / " + std::to_string(this->player->getAtrComp()->maxHP);
	this->hpBarText.setString(this->hpBarStr);
	this->hpBarText.setPosition(this->hpBarBg.getPosition().x + (this->hpBarBg.getSize().x / 2 - this->hpBarText.getGlobalBounds().width / 2),
		this->hpBarBg.getPosition().y + (this->hpBarBg.getSize().y / 2 - this->hpBarText.getGlobalBounds().height));
}

void PlayerGUI::renderHp(sf::RenderTarget& target)
{
	target.draw(this->hpBarBg);
	target.draw(this->hpBarCont);
	target.draw(this->hpBarText);
}

void PlayerGUI::updateXp()
{
	float percent = static_cast<float>(this->player->getAtrComp()->xp)
		/ static_cast<float>(this->player->getAtrComp()->xpNext);

	this->xpBarCont.setSize(sf::Vector2f(static_cast<float>(std::floor(this->xpBarMaxWidth * percent)), this->xpBarCont.getSize().y));
	this->xpBarStr = std::to_string(this->player->getAtrComp()->xp) + " / " + std::to_string(this->player->getAtrComp()->xpNext);
	this->xpBarText.setString(this->xpBarStr);
	this->xpBarText.setPosition(this->xpBarBg.getPosition().x + (this->xpBarBg.getSize().x / 2 - this->xpBarText.getGlobalBounds().width / 2),
		this->xpBarBg.getPosition().y + (this->xpBarBg.getSize().y / 2 - this->xpBarText.getGlobalBounds().height));
}

void PlayerGUI::renderXp(sf::RenderTarget& target)
{
	target.draw(this->xpBarBg);
	target.draw(this->xpBarCont);
	target.draw(this->xpBarText);
}

void PlayerGUI::updateLVL()
{
	this->lvlBarStr = std::to_string(this->player->getAtrComp()->lvl);
	this->lvlBarText.setString(this->lvlBarStr);
	this->lvlBarText.setPosition(this->lvlBar.getPosition().x + (this->lvlBar.getSize().x / 2 - this->lvlBarText.getGlobalBounds().width / 2),
		this->lvlBar.getPosition().y + (this->lvlBar.getSize().y / 2 - this->lvlBarText.getGlobalBounds().height ));
}

void PlayerGUI::renderLVL(sf::RenderTarget& target)
{
	target.draw(this->lvlBar);
	target.draw(this->lvlBarText);
}
