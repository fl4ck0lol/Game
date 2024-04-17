#include "stdafx.h"
#include "MainMenuState.h"
using namespace GUI;

void MainMenuState::InitialiseKeyBinds()
{
	std::ifstream ifs("Config/mainmenu_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";
		while (ifs >> key >> key2)
		{
			this->keyBinds[key] = this->supportedKeys->at(key2);
		}
	}
	ifs.close();

}

void MainMenuState::InitialiseFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Thin.ttf"))
	{
		throw("ERROR:FONT NOT LOADED");
	}
}

void MainMenuState::IntitialiseButtons()
{
	const sf::VideoMode& vm = this->stateData->gSettings->resolution;
	float buttonSize_x, buttonSize_y;
	buttonSize_x = 260;
	buttonSize_y = 80;
	this->buttons["GAME_STATE"] = new Button(centerButtons(buttonSize_x), GUI::PixelPercentY(32.41, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), L"НОВА ИГРА", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->buttons["SETTINGS"] = new Button(centerButtons(buttonSize_x), GUI::PixelPercentY(46.3, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), L"НАСТРОЙКИ", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->buttons["EDITOR"] = new Button(centerButtons(buttonSize_x), GUI::PixelPercentY(60.19, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), L"EDITOR", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);
	
	this->buttons["END_STATE"] = new Button(centerButtons(buttonSize_x), GUI::PixelPercentY(74.07, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), L"ИЗХОД", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);
}

void MainMenuState::InitialiseBackGround()
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;
	this->Background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->Background.setFillColor(sf::Color(228, 143, 69, 255));
	
	this->container.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), GUI::PixelPercentY(13.89, vm)));
	this->container.setPosition(sf::Vector2f(0, GUI::PixelPercentY(3.72, vm)));
	this->container.setFillColor(sf::Color(153, 77, 28, 255));
}

const int MainMenuState::centerButtons(float button_x)
{
	return (this->window->getSize().x / 2) - (button_x / 2);
}

MainMenuState::MainMenuState(StateData* stateData) : State(stateData)
{
	this->InitialiseBackGround();
	this->InitialiseKeyBinds();
	this->InitialiseFonts();
	this->IntitialiseButtons();	
}

MainMenuState::~MainMenuState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}
}


void MainMenuState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
		this->endState();
}

void MainMenuState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons();
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->Background);	
	this->renderButtons(*target);
	target->draw(this->container);

	sf::Text mousetext;
	mousetext.setPosition(this->mousePositionView.x, this->mousePositionView.y - 30);
	mousetext.setFont(this->font);
	mousetext.setCharacterSize(24);
	std::stringstream ss;
	ss << mousePositionScreen.x << " " << mousePositionScreen.y;
	mousetext.setString(ss.str());

	target->draw(mousetext);
}

void MainMenuState::updateButtons()
{

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow);
	}

	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	if (this->buttons["SETTINGS"]->isPressed())
	{
		this->states->push(new SettingsState(this->stateData));
	}

	if (this->buttons["EDITOR"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	if (this->buttons["END_STATE"]->isPressed())
	{
		this->endState();
	}

	const sf::VideoMode& vm = this->stateData->gSettings->resolution;

	this->buttons["GAME_STATE"]->updateProperties(centerButtons(GUI::PixelPercentX(13.13, vm)), GUI::PixelPercentY(32.41, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), GUI::calcCharSize(vm));
	this->buttons["SETTINGS"]->updateProperties(centerButtons(GUI::PixelPercentX(13.13, vm)), GUI::PixelPercentY(46.3, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), GUI::calcCharSize(vm));
	this->buttons["EDITOR"]->updateProperties(centerButtons(GUI::PixelPercentX(13.13, vm)), GUI::PixelPercentY(60.19, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), GUI::calcCharSize(vm));
	this->buttons["END_STATE"]->updateProperties(centerButtons(GUI::PixelPercentX(13.13, vm)), GUI::PixelPercentY(74.07, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), GUI::calcCharSize(vm));
}

void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}
