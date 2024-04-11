#include "stdafx.h"
#include "EditorState.h"

using namespace GUI;

void EditorState::InitialiseVars()
{
	this->textureRect = sf::IntRect(0, 0, 16, 16);
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
	this->pausemenu->addButton("QUIT", 900.f, L"Изход");
}

void EditorState::InitialiseTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10.f, 10.f);
}

void EditorState::InitialiseGUI()
{
	this->selector.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	this->selector.setFillColor(sf::Color(255, 255, 255, 50));
	this->selector.setOutlineThickness(1.f);
	this->selector.setOutlineColor(sf::Color::Red);
	this->selector.setTexture(this->tileMap->getTileTexture());

	this->textureSelector = new TextureSelector(20.f, 20.f, 500.f, 500.f,this->stateData->gridSize, this->tileMap->getTileTexture());
}


void EditorState::InitialiseBackGround()
{
	
}

EditorState::EditorState(StateData* stateData) : lastState(0), State(stateData), pressOnce(0)
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
}

void EditorState::update(const float& dt)
{
	this->updateInput(dt);
	this->updateMousePositions();

	if (!this->paused)
	{
		this->updateGUI();
		this->updateButtons();
		this->updateTile(dt);
	}
	else
	{
		this->pausemenu->update(this->mousePositionView);
		this->updatePauseMenuButtons();
	}

}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->tileMap->render(*target);

	this->renderButtons(*target);
	this->renderGUI(*target);

	if (this->paused)
	{
		this->pausemenu->render(*target);
	}
}

void EditorState::updateButtons()
{

	for (auto& it : this->buttons)
	{
		it.second->update(mousePositionView);
	}

}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
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
	ss << mousePositionScreen.x << " " << mousePositionScreen.y << " " << this->textureRect.left << " " << textureRect.top << "\n" << mousePositionGrid.x << mousePositionGrid.y;
	this->cursorText.setString(ss.str());
	this->cursorText.setPosition(this->mousePositionView.x - 100.f, this->mousePositionView.y - 30);

}

void EditorState::renderGUI(sf::RenderTarget& target)
{
	if(!this->textureSelector->getActive())
		target.draw(this->selector);
	this->textureSelector->render(target);
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
			this->tileMap->AddTile(this->mousePositionGrid.x, this->mousePositionGrid.y, 0, this->textureRect);
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
