	#include "stdafx.h"
#include "EditorState.h"

using namespace GUI;

void EditorState::InitialiseVars()
{
	this->textureRect = sf::IntRect(0, 0, 16, 16);
	this->collision = 0;
	this->type = Tile_types::DEFAULT;

	this->mainView.setSize(sf::Vector2f(this->stateData->gSettings->resolution.width, this->stateData->gSettings->resolution.height));
	this->mainView.setCenter(this->stateData->gSettings->resolution.width / 2, this->stateData->gSettings->resolution.height / 2);

	this->cameraSpeed = 100.f;
}

void EditorState::InitialiseKeyBinds()
{
	std::ifstream ifs("Config/editor_keybinds.ini");

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

void EditorState::InitialiseFonts()
{
	if (!this->font.loadFromFile("Fonts/Roboto-Thin.ttf"))
	{
		throw("ERROR:FONT NOT LOADED");
	}
}

void EditorState::InitialiseText()
{
	this->cursorText.setFont(this->font);
	this->cursorText.setCharacterSize(24);
	this->cursorText.setFillColor(sf::Color::White);
}

void EditorState::IntitialiseButtons()
{
	
}

void EditorState::InitialisePauseMenu()
{
	this->pausemenu = new PauseMenu(*this->window, this->font);
	this->pausemenu->addButton("QUIT", 900.f, L"ИЗХОД");

}

void EditorState::InitialiseTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10.f, 10.f, "Resources/GRASS+.png");
	this->tileMap->loadFromFile("Resources/map.txt");
}

void EditorState::InitialiseGUI()
{
	this->selector.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selector.setFillColor(sf::Color(255, 255, 255, 50));
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setTexture(this->tileMap->getTileTexture());

	this->textureSelector = new TextureSelector(
		this->window->getSize().x - 520.f, 
		this->window->getSize().y - (this->window->getSize().y - 20.f), 
		500.f, 500.f, this->stateData->gridSize, this->tileMap->getTileTexture());

	this->buttons["SHOW_TEXTURE"] = new Button(
		static_cast<float>(this->window->getSize().x - 410.f),
		static_cast<float>(this->window->getSize().y - (this->window->getSize().y - 540.f)),
			300, 50, L"ТЕКСТУРИ", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->sideBar.setSize(sf::Vector2f(250.f, this->window->getSize().y));
	this->sideBar.setFillColor(sf::Color(255, 255, 255, 50));
	this->sideBar.setOutlineThickness(1.f);
	this->sideBar.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sideBarButtons["SAVE"] = new Button(
		static_cast<float>((this->sideBar.getSize().x / 2) - 150.f),
		static_cast<float>(100.f),
		300, 50, L"ЗАПАЗИ", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

	this->sideBarButtons["LOAD"] = new Button(
		static_cast<float>((this->sideBar.getSize().x / 2) - 150.f),
		static_cast<float>(400.f),
		300, 50, L"ЗАРЕДИ", sf::Color(52, 61, 70, 50), &this->font,
		sf::Color(192, 197, 206, 0), sf::Color(101, 115, 126, 0), sf::Color(52, 61, 70, 0), 50,
		sf::Color(107, 36, 12, 250), sf::Color(245, 204, 160, 255), sf::Color(52, 61, 70, 200), sf::Color::Transparent, 0);

}


void EditorState::InitialiseBackGround()
{
	
}

EditorState::EditorState(StateData* stateData) : lastState(0), State(stateData), pressOnce(0), showSidebar(0)
{
	this->InitialiseVars();
	this->InitialiseBackGround();
	this->InitialiseKeyBinds();
	this->InitialiseFonts();
	this->InitialiseText();
	this->InitialisePauseMenu();
	this->IntitialiseButtons();
	this->InitialiseTileMap();
	this->InitialiseGUI();
}

EditorState::~EditorState()
{
	for (auto it = this->buttons.begin(); it != this->buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pausemenu;

	delete this->tileMap;

	delete this->textureSelector;
}

void EditorState::updateInput(const float& dt)
{
	//p menu
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["PAUSEMENU"])) && this->lastState == 0)
	{
		this->lastState = 1;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["PAUSEMENU"])) && this->lastState == 1)
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();

		this->lastState = 0;
	}

	//side bar
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("SHOWBAR"))) && this->lastState == 0)
	{
		this->lastState = 2;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("SHOWBAR"))) && this->lastState == 2)
	{
		if (this->showSidebar == 0)
			this->showSidebar = 1;
		else
			this->showSidebar = 0;

		this->lastState = 0;
	}

	//collision
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("COLLISION"))) && this->lastState == 0)
	{
		this->lastState = 3;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("COLLISION"))) && this->lastState == 3)
	{
		if (this->collision == 0)
			this->collision = 1;
		else
			this->collision = 0;

		this->lastState = 0;
	}

	//type up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPEUP"))) && this->lastState == 0)
	{
		this->lastState = 4;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPEUP"))) && this->lastState == 4)
	{
		this->type++;

		this->lastState = 0;
	}

	//type down
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPEDOWN"))) && this->lastState == 0)
	{
		this->lastState = 5;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds.at("TYPEDOWN"))) && this->lastState == 5)
	{
		this->type--;

		this->lastState = 0;
	}

	//texture button
	if (this->buttons["SHOW_TEXTURE"]->isPressed())
	{
		this->textureSelector->HideUnhide();
	}


	//side bar buttons
	if (this->sideBarButtons["SAVE"]->isPressed())
	{
		this->tileMap->saveToFile("Resources/map.txt");
	}

	if (this->sideBarButtons["LOAD"]->isPressed())
	{
		this->tileMap->loadFromFile("Resources/map.txt");
	}

	//camera

	//up
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CAMERAUP"])))
	{
		this->mainView.move(0.f, this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CAMERADOWN"])))
	{
		this->mainView.move(0.f, -this->cameraSpeed * dt);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CAMERALEFT"])))
	{
		this->mainView.move(this->cameraSpeed * dt, 0.f);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keyBinds["CAMERARIGHT"])))
	{
		this->mainView.move(-this->cameraSpeed * dt, 0.f);
	}
}

void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions(&this->mainView);

	if (!this->paused && !this->showSidebar)
	{
		this->updateGUI();
		this->updateButtons();
		this->updateTile(dt);
	}
	else
	{
		this->pausemenu->update(this->mousePositionWindow);
		this->updatePauseMenuButtons();
	}

	if (!this->paused && this->showSidebar)
	{
		this->updateSideBarButtons();
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->setView(this->mainView);

	this->tileMap->render(*target);

	target->setView(this->window->getDefaultView());

	this->renderButtons(*target);
	this->renderGUI(*target);

	if (this->paused)
	{
		target->setView(this->window->getDefaultView());
		this->pausemenu->render(*target);
	}

	if (this->showSidebar)
	{
		this->renderSideBarButtons(*target);
	}
}

void EditorState::updateButtons()
{

	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePositionWindow);
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void EditorState::renderSideBarButtons(sf::RenderTarget& target)
{
	target.setView(this->window->getDefaultView());
	for (auto& it : this->sideBarButtons)
	{
		it.second->render(target);
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pausemenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::updateGUI()
{
	this->textureSelector->update(this->mousePositionWindow);

	if (!this->textureSelector->getActive())
	{
		this->selector.setPosition(this->mousePositionGrid.x * this->stateData->gridSize, this->mousePositionGrid.y * this->stateData->gridSize);
		this->selector.setTextureRect(this->textureRect);
	}

	std::stringstream ss;
	ss << mousePositionScreen.x
		<< " " << mousePositionScreen.y
		<< " " << this->textureRect.left
		<< " " << textureRect.top << "\n"
		<< mousePositionGrid.x
		<< mousePositionGrid.y
		<< "\ncollision: " << this->collision
		<< "\ntype: " << this->type;
	this->cursorText.setString(ss.str());
	this->cursorText.setPosition(this->mousePositionView.x - 100.f, this->mousePositionView.y - 30);

}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	if (!this->textureSelector->getActive())
	{
		target.setView(this->mainView);
		target.draw(this->selector);
	}

	target.setView(this->window->getDefaultView());
	this->textureSelector->render(target);

	if (this->showSidebar)
	{
		target.draw(sideBar);
	}

	target.setView(this->mainView);
	target.draw(this->cursorText);

}

void EditorState::updateTile(const float& dt)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressOnce != 1)
	{
		this->pressOnce = 1;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left) && pressOnce == 1)
	{
		this->pressOnce = 0;

		if (!this->textureSelector->getActive())
			this->tileMap->AddTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0, this->textureRect, this->collision, this->type);

		else
			this->textureRect = this->textureSelector->getTextureRect();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Right) && pressOnce != 2)
	{
		this->pressOnce = 2;
	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Right) && pressOnce == 2)
	{
		this->pressOnce = 0;
		if (!this->textureSelector->getActive())
			this->tileMap->RemoveTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0);
	}

}

void EditorState::updateSideBarButtons()
{
	for (auto& it : this->sideBarButtons)
	{
		it.second->update(this->mousePositionWindow);
	}
}
