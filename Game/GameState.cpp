#include "stdafx.h"
#include "GameState.h"
#include "Player.h"
#include "allEnemy.h"

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
	: State(stateData), lastState(0), end(0)
{
	this->InitialiseRender();
	this->InitialiseView();
	this->InitialiseKeyBinds();
	this->InitialiseTextures();
	this->InitialisePlayers();
	this->InitialiseEnemySystem();
	this->InitialiseTileMap();
	this->InitialiseFonts();
	this->InitialisePauseMenu();
	this->InitialiseShaders();
	this->InitialisePlayerGUI();
	this->InitialiseEndScreen();
}
	
GameState::~GameState()
{
	delete this->player;
	delete this->pausemenu;
	delete this->playerGUI;
	delete this->tileMap;
	delete this->sword;
	delete this->enemySystem;

	for (size_t i = 0; i < this->activeEnemies.size(); ++i)
	{
		delete this->activeEnemies[i];
	}

	for (auto it = this->endButtons.begin(); it != this->endButtons.end(); ++it)
	{
		delete it->second;
	}
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

	if (!(this->player->returnCurrentHp() <= 0))
	{
		this->updateInput(dt);

		if (!this->paused)
		{
			this->updateView(dt);

			this->updatePlayerInput(dt);

			this->updateTileMap(dt);

			this->player->update(dt, this->mousePositionView);

			this->playerGUI->update(dt);

			this->updateEnemiesAndCombat(dt);
		}
		else
		{
			this->pausemenu->update(this->mousePositionWindow);
			this->updatePauseMenuButtons();
		}
	}
	else
	{
		this->end = 1;
		for (auto& i : endButtons)
		{
			i.second->update(this->mousePositionWindow);
		}
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

	this->tileMap->render(this->renderTexture, this->viewGridPos, &this->coreShader, false, this->player->getPlayerCenter());

	for (size_t enemy = 0; enemy < this->activeEnemies.size(); ++enemy)
	{
		this->activeEnemies[enemy]->render(this->renderTexture, &this->coreShader, this->player);
	}

	this->player->render(this->renderTexture, &this->coreShader);


	this->tileMap->renderDeferred(this->renderTexture, this->player->getPlayerCenter(), &this->coreShader);

	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture, &this->coreShader, this->player);

	if (this->paused)
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pausemenu->render(this->renderTexture);
	}

	this->renderTexture.display();
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);

	if (end == 1)
	{
		target->draw(this->endRect);
		target->draw(this->endText);

		for (auto& i : endButtons)
		{
			i.second->render(*target);
		}

		if (this->endButtons["NEWGAME"]->isPressed())
		{
			this->states->pop();
			this->states->push(new GameState(stateData));
		}

		if (this->endButtons["EXIT"]->isPressed())
		{
			this->states->pop();
		}
	}
}

void GameState::InitialiseView()
{
	this->view.setSize(sf::Vector2f(this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height));
	this->view.setCenter(sf::Vector2f(this->stateData->gSettings->resolution.width / 2, this->stateData->gSettings->resolution.height / 2));
}

void GameState::InitialiseTextures()
{
	if(!this->textures["PLAYER"].loadFromFile("Resources/player/PLAYER_SHEET2.png"))
		throw "ERRORR GameState player texture doesnt load";

	if (!this->textures["RAT"].loadFromFile("Resources/Enemy/rat1_60X64.png"))
		throw "ERRORR GameState player texture doesnt load";
}

void GameState::InitialisePlayers()
{
	this->player = new Player(this->textures["PLAYER"], 100, 100);
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::X))
	{
		this->player->loseHP(6);
	}


}

void GameState::updateView(const float& dt)
{

	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePositionWindow.x) - static_cast<float>(this->stateData->gSettings->resolution.width / 2)) / 10.f),
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePositionWindow.y) - static_cast<float>(this->stateData->gSettings->resolution.height / 2)) / 10.f)
	);

	this->viewGridPos.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPos.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);
}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updateCombat(Enemy* enemy, const int index, const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && 
		enemy->getGlobalBounds().contains(this->mousePositionView) &&
		enemy->getDistance(this->player) < this->player->getWeapon()->getRange())
	{
		if (this->player->getWeapon()->getAttackTimer() && 
			enemy->getGlobalBounds().contains(this->mousePositionView) &&
			enemy->getDistance(this->player) < this->player->getWeapon()->getRange())
		{
			enemy->loseHP(this->player->getWeapon()->getDmg());
		}
	}

	if (enemy->getGlobalBounds().intersects(this->player->getGlobalBounds()))
	{
		if (enemy->getAttackTimer())
		{
			this->player->loseHP(1);
		}
	}

}

void GameState::updateEnemiesAndCombat(const float& dt)
{
	unsigned index = 0;
	for (auto& enemy : this->activeEnemies)
	{
		enemy->update(dt, this->mousePositionView);
		this->updateCombat(enemy, index, dt);
		enemy->update(dt, this->mousePositionView);

		this->tileMap->updateTileCollision(enemy, dt);
		this->tileMap->updateWorldBoundsCollision(enemy, dt);

		if (enemy->isDead())
		{
			this->player->gainXP(enemy->giveXp());	

			this->enemySystem->removeEnemy(index);

			--index;
		}
		++index;
	}
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
	sf::VideoMode& vm = this->stateData->gSettings->resolution;
	this->pausemenu = new PauseMenu(this->stateData->gSettings->resolution, this->font);
	this->pausemenu->addButton("QUIT", GUI::PixelPercentY(83.33, vm), GUI::PixelPercentX(13.13, vm), GUI::PixelPercentY(7.41, vm), GUI::calcCharSize(vm), L"Изход");
}

void GameState::InitialiseTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 100, 100, "Resources/tilesheet3.png");
	this->tileMap->loadFromFile("Resources/map.txt");

}

void GameState::InitialiseRender()
{
	this->renderTexture.create(this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height);
	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(sf::IntRect(0, 0, this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height));
}

void GameState::InitialisePlayerGUI()
{
	sf::VideoMode& vm = this->stateData->gSettings->resolution;
	this->playerGUI = new PlayerGUI(this->player, this->font, vm);
}

void GameState::InitialiseShaders()
{
	if (!this->coreShader.loadFromFile("vertex_shader.vert", "fragment_shader.frag"))
		std::cout << "shader didnt load \n";
}

void GameState::InitialiseEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures, *this->player);
}

void GameState::InitialiseEndScreen()
{
	this->endRect.setSize(sf::Vector2f(this->window->getSize().x / 3, this->window->getSize().y));
	this->endRect.setPosition(this->window->getSize().x / 2 - this->endRect.getSize().x / 2, 0);
	this->endRect.setFillColor(sf::Color(20, 20, 20, 150));

	this->endText.setString(L"КРАЙ");
	this->endText.setFont(this->font);
	this->endText.setCharacterSize(50);
	this->endText.setFillColor(sf::Color::White);
	this->endText.setPosition(this->endRect.getPosition().x + (this->endRect.getSize().x / 2) - this->endText.getGlobalBounds().width / 2, 150);

	int x = this->endRect.getPosition().x + (this->endRect.getSize().x / 2) - 100;

	this->endButtons["NEWGAME"] = new GUI::Button(x, 700, 200, 150, L"НОВА ИГРА", sf::Color(52, 61, 70, 0), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(192, 197, 206, 250), sf::Color(101, 115, 126, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->endButtons["EXIT"] = new GUI::Button(x, 850, 200, 150, L"ИЗХОД", sf::Color(52, 61, 70, 0), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(192, 197, 206, 250), sf::Color(101, 115, 126, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

}
