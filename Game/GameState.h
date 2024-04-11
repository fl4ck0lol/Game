#pragma once
#include "Entity.h"
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "TileMap.h"

class GameState :
    public State
{
private:

    PauseMenu* pausemenu;
    Player* player;
    void InitialiseKeyBinds();
    sf::RectangleShape BG;
    sf::Font font;
    short unsigned lastState;
    TileMap* tileMap;

    void InitialiseTextures();
    void InitialisePlayers();
    void InitialiseFonts();
    void InitialisePauseMenu();
    void InitialiseTileMap();

public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void updatePlayerInput(const float& dt);
    void update(const float& dt);
    void updatePauseMenuButtons();
    void render(sf::RenderTarget* target = nullptr);

    void updateInput(const float& dt);
};

