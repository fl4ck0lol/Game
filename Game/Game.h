#pragma once
#include "MainMenuState.h"
#include "GraphicSettings.h"

class Game
{
private:

	float gridSize;
	float dt;

	GraphicSettings gSettings;

	sf::RenderWindow *window;
	sf::Event sfEvent;
	sf::Clock dtClock;

	std::stack<State*> states;
	std::map<std::string, int> supportedKeys;

	StateData stateData;

	void initialiseVariables();
	void initialiseWindow();
	void initialiseState();
	void initialiseKeys();
	void initialiseGraphicSetings();
	void initialiseStateData();
	
public:

	Game();
	virtual ~Game();
	
	void endApp();
	void update();
	void render();
	void run();
	void updateSFMLevents();
	void updateDT();	
};
