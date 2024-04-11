#pragma once
#include "GameState.h"
#include "MainMenuState.h"
#include "GraphicSettings.h"

class Game
{
private:

	GraphicSettings gSettings;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float dt;

	void initialiseVariebles();
	void initialiseWindow();
	void initialiseState();
	void initialiseKeys();
	void initialiseGraphicSetings();
	void initialiseStateData();

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	StateData stateData;

	float gridSize;
	
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




