#pragma once

#include"GraphicSettings.h"
#include"Player.h"

class Player;
class GraphicSettings;
class State;

class StateData
{
public:
	StateData()
	{
		
	}

	float gridSize;
	sf::RenderWindow* window;
	std::map < std::string, int > * supportedKeys;
	std::stack<State*>* states;
	GraphicSettings* gSettings;
};

class State
{

protected:
	sf::RenderWindow* window;
	std::map<std::string, sf::Texture> textures;	
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keyBinds;
	sf::Vector2i mousePositionScreen;
	sf::Vector2i mousePositionWindow;
	sf::Vector2f mousePositionView;
	sf::Vector2u mousePositionGrid;
	std::stack<State*>* states;

	virtual void InitialiseKeyBinds() = 0;

	bool quit;
	bool paused;
	float gridSize;

	StateData* stateData;


public:
	State(StateData* stateData);
	virtual ~State();

	const bool& getQuit() const;

	virtual void updateMousePositions(sf::View* view = nullptr);
	void endState();
	virtual void updateInput(const float& dt) = 0;
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	void pauseState();
	void unpauseState();
};

