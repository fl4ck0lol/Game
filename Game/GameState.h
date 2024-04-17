#pragma once
#include "Entity.h"
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"

class Player;
class PauseMenu;
class TileMap;
class sf::View;
class sf::Font;
class sf::RenderTexture;
class PlayerGUI;

class GameState :
    public State
{
private:

    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Shader coreShader;

    PauseMenu* pausemenu;
    Player* player;
    PlayerGUI* playerGUI;
    sf::RectangleShape BG;
    sf::Font font;
    short unsigned lastState;
    TileMap* tileMap;

    void InitialiseKeyBinds();
    void InitialiseView();
    void InitialiseTextures();
    void InitialisePlayers();
    void InitialiseFonts();
    void InitialisePauseMenu();
    void InitialiseTileMap();
    void InitialiseRender();
    void InitialisePlayerGUI();
    void InitialiseShaders();

public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void updatePlayerInput(const float& dt);
    void update(const float& dt);
    void updatePauseMenuButtons();
    void render(sf::RenderTarget* target = nullptr);
    void updateInput(const float& dt);
    void updateView(const float& dt);
    void updateTileMap(const float& dt);
    void updatePlayerGUI(const float& dt);
};

