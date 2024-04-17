#include "stdafx.h"
#include "SettingsState.h"
using namespace GUI;

void SettingsState::InitialiseKeyBinds()
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

void SettingsState::InitialiseFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Thin.ttf"))
	{
		throw("ERROR:FONT NOT LOADED");
	}
}

void SettingsState::IntitialiseButtons()
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;

	this->buttons["END_STATE"] = new Button(GUI::PixelPercentX(80, vm), 
		GUI::PixelPercentY(80, vm),
		GUI::PixelPercentX(13.13, vm),
		GUI::PixelPercentY(7.41, vm), L"НАЗАД", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(192, 197, 206, 250), sf::Color(101, 115, 126, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->buttons["APPLY"] = new Button(GUI::PixelPercentX(80, vm),
		GUI::PixelPercentY(65, vm),
		GUI::PixelPercentX(13.13, vm),
		GUI::PixelPercentY(7.41, vm), L"ПРИЛОЖИ", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), GUI::calcCharSize(vm),
		sf::Color(192, 197, 206, 250), sf::Color(101, 115, 126, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	std::vector<std::wstring> modes_str;

	std::wstring res = L"РЕЗОЛЮЦИЯ";
	modes_str.push_back(res);

	for (auto& i : this->vmodes)
	{
		modes_str.push_back(std::to_wstring(i.width) + L'x' + std::to_wstring(i.height));
	}

	this->dropDownButtons["RESOLUTION"] = new DropDownList(GUI::PixelPercentX(19.19, vm),
		GUI::PixelPercentY(27.78, vm), GUI::PixelPercentX(12.63, vm),
		GUI::PixelPercentY(4.63, vm), this->font,
		GUI::calcCharSize(vm) - 20, modes_str.data(),
		modes_str.size(), 0);
}

const int SettingsState::centerButtons(float button_x)
{
	return (static_cast<float>(this->window->getSize().x) / 2) - (button_x / 2);
}

void SettingsState::InitialiseBackGround()
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;
	this->Background.setSize(sf::Vector2f(static_cast<float>(this->window->getSize().x), static_cast<float>(this->window->getSize().y)));
	this->Background.setFillColor(sf::Color(228, 143, 69, 255));

	this->container.setSize(sf::Vector2f(GUI::PixelPercentX(45.45, vm), GUI::PixelPercentY(18.52, vm)));
	this->container.setPosition(0 , 75);
	this->container.setFillColor(sf::Color(153, 77, 28, 255));
}

void SettingsState::initialiseText()
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(GUI::PixelPercentX(5.05, vm), GUI::PixelPercentY(27.78, vm)));
	this->optionsText.setCharacterSize(GUI::calcCharSize(vm));
	this->optionsText.setFillColor(sf::Color::Black);
	this->optionsText.setString(L"Резoлюция \n\n Цял екран \n\n antialiasing \n\n vsync");

	this->settingsText.setCharacterSize(GUI::calcCharSize(vm) * 2);
	this->settingsText.setFont(this->font);
	this->settingsText.setString(L"Настройки");
	this->settingsText.setPosition(GUI::PixelPercentX(9.09, vm), GUI::PixelPercentY(9.05, vm));
}

void SettingsState::initialiseVars()
{
	this->vmodes = sf::VideoMode::getFullscreenModes();
}

SettingsState::SettingsState(StateData* stateData) : State(stateData)
{
	this->initialiseVars();
	this->InitialiseKeyBinds();
	this->InitialiseFonts();
	this->InitialiseBackGround();
	this->initialiseText();
	this->IntitialiseButtons();
}

SettingsState::~SettingsState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	for (auto it = this->dropDownButtons.begin(); it != this->dropDownButtons.end(); ++it)
	{
		delete it->second;
	}
}


void SettingsState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))))
		this->endState();
}

void SettingsState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();
	this->updateButtons(dt);
}

void SettingsState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->Background);
	target->draw(this->container);
	target->draw(this->settingsText);
	target->draw(this->textContainer);
	target->draw(this->optionsText);

	this->renderButtons(*target);

	sf::Text mousetext;
	mousetext.setPosition(this->mousePositionView.x, this->mousePositionView.y - 30);
	mousetext.setFont(this->font);
	mousetext.setCharacterSize(24);
	std::stringstream ss;
	ss << mousePositionScreen.x << " " << mousePositionScreen.y;
	mousetext.setString(ss.str());

	target->draw(mousetext);

}

void SettingsState::updateButtons(const float& dt)
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow);
	}


	if (this->buttons["END_STATE"]->isPressed())
	{
		this->endState();
	}

	if (this->buttons["APPLY"]->isPressed())
	{
		if (this->dropDownButtons["RESOLUTION"]->getActiveElemID() != 0)
		{
			this->stateData->gSettings->resolution = this->vmodes[this->dropDownButtons["RESOLUTION"]->getActiveElemID() - 1];
			this->window->create(this->stateData->gSettings->resolution, this->stateData->gSettings->title, sf::Style::Default);
			this->InitialiseBackGround();
			this->initialiseText();
			this->buttons["APPLY"]->updateProperties(GUI::PixelPercentX(80, vm), 
				GUI::PixelPercentY(65, vm),
				GUI::PixelPercentX(13.13, vm),
				GUI::PixelPercentY(7.41, vm),
				GUI::calcCharSize(vm));

			this->buttons["END_STATE"]->updateProperties(GUI::PixelPercentX(80, vm),
				GUI::PixelPercentY(75, vm),
				GUI::PixelPercentX(13.13, vm),
				GUI::PixelPercentY(7.41, vm),
				GUI::calcCharSize(vm));

		}
	}

	for (auto& it : this->dropDownButtons)
	{
		it.second->update(this->mousePositionWindow, dt);
	}
}

void SettingsState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	for (auto& it : this->dropDownButtons)
	{
		it.second->render(target);
	}
}
