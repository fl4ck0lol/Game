#include "stdafx.h"
#include "Game.h"

void Game::initialiseVariables()
{
	this->window = NULL;
	this->dt = 0.f;
	this->gridSize = 64.f;
}

void Game::initialiseWindow()
{
	if(this->gSettings.fullscreen)
		this->window = new sf::RenderWindow(this->gSettings.resolution, this->gSettings.title, sf::Style::Fullscreen, this->gSettings.contextSettings);
	else
		this->window = new sf::RenderWindow(this->gSettings.resolution, this->gSettings.title, sf::Style::Titlebar | sf::Style::Close, this->gSettings.contextSettings);

	this->window->setFramerateLimit(this->gSettings.frameLimit);
	this->window->setVerticalSyncEnabled(this->gSettings.vsync);

}

void Game::initialiseKeys()
{
	std::ifstream ifs("Config/supported_keys.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		int value = 0;
		while (ifs >> key >> value)
		{
			this->supportedKeys[key] = value;		
		}
	}
	ifs.close();
}

void Game::initialiseGraphicSetings()
{
	this->gSettings.loadFromFile("Config/graphic_settings.ini");
}

void Game::initialiseStateData()
{
	this->stateData.window = this->window;
	this->stateData.gSettings = &this->gSettings;
	this->stateData.supportedKeys = &this->supportedKeys;
	this->stateData.states = &this->states;
	this->stateData.gridSize = this->gridSize;	
}

void Game::initialiseState()
{
	this->states.push(new MainMenuState(&this->stateData));
}

void Game::endApp()
{
	std::cout << "ending app";
}

void Game::update()
{
	this->updateSFMLevents();

	if (!this->states.empty())
	{
		if (this->window->hasFocus())
		{
			this->states.top()->update(this->dt);

			if (this->states.top()->getQuit())
			{
				this->states.top()->endState();
				delete this->states.top();
				this->states.pop();
			}
		}
	}
	else
	{
		this->endApp();
		this->window->close();
	}	
}

void Game::render()
{
	this->window->clear();
	
	if(!this->states.empty())
		this->states.top()->render();

	this->window->display();
}

void Game::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
		this->updateSFMLevents();
	}
}

void Game::updateSFMLevents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void Game::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}
//---------------------------------
Game::Game()
{
	this->initialiseVariables();
	this->initialiseGraphicSetings();
	this->initialiseWindow();
	this->initialiseKeys();
	this->initialiseStateData();
	this->initialiseState();
}

Game::~Game()
{
	delete this->window;

	while (!this->states.empty())
	{
		delete this->states.top();
		this->states.pop();
	}
}