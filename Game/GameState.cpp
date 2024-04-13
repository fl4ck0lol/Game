#include "stdafx.h"
#include "GameState.h"
#include "Player.h"

void GameState::InitialiseKeyBinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

GameState::GameState(StateData* stateData)
	: State(stateData), lastState(0)	
{
	this->InitialiseView();
	this->InitialiseKeyBinds();
	this->InitialiseTextures();
	this->InitialisePlayers();
	this->InitialiseFonts();
	this->InitialisePauseMenu();
	this->InitialiseTileMap();
	this->InitialiseRender();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pausemenu;
}

void GameState::updatePlayerInput(const float& dt)
{

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view);
	this->updateInput(dt);

	if (!this->paused)
	{
		this->updateView(dt);
		this->updatePlayerInput(dt);
		this->player->update(dt);
	}
	else
	{
		this->pausemenu->update(this->mousePositionWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pausemenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;
	this->renderTexture.clear();

	this->renderTexture.setView(this->view);
	this->tileMap->render(this->renderTexture);

	this->player->render(this->renderTexture);

	if (this->paused)
	{
		this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pausemenu->render(this->renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

void GameState::InitialiseView()
{
	this->view.setSize(sf::Vector2f(this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height));
	this->view.setCenter(sf::Vector2f(this->stateData->gSettings->resolution.width / 2, this->stateData->gSettings->resolution.height / 2));
}

void GameState::InitialiseTextures()
{

	if(!this->textures["player_state_idle"].loadFromFile("Resources/player/AnimationSheet_Character1.png"))
		throw "ERRORR GameState player texture doesnt load";
}

void GameState::InitialisePlayers()
{
	this->player = new Player(this->textures["player_state_idle"], 0, 0);
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->lastState == 0)
	{
		this->lastState = 1;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P) && this->lastState == 1)
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();

		this->lastState = 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->lastState == 0)
	{
		this->lastState = 2;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("CLOSE"))) && this->lastState == 2)
	{
		this->endState();

		this->lastState = 0;
	}
}

void GameState::updateView(const float& dt)
{
	this->view.setCenter(this->player->getPosition());
}

void GameState::InitialiseFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Thin.ttf"))
	{
		throw("ERROR:FONT NOT LOADED");
	}
}

void GameState::InitialisePauseMenu()
{
	this->pausemenu = new PauseMenu(*this->window, this->font);
	this->pausemenu->addButton("QUIT", 900.f, L"Изход");
}

void GameState::InitialiseTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10.f, 10.f, "Resources/GRASS+.png");
	this->tileMap->loadFromFile("Resources/map.txt");
}

void GameState::InitialiseRender()
{
	this->renderTexture.create(this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height));
}
