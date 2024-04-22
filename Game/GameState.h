#pragma once
#include "Entity.h"
#include "State.h"
#include "Player.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Enemy.h"

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

    EnemySystem* enemySystem;
        
    sf::View view;
    sf::Vector2i viewGridPos;

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

    std::vector<Enemy*> activeEnemies;

    Sword* sword;

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
    void InitialiseEnemySystem();

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
    void updateCombat(Enemy* enemy, const int index, const float& dt);
    void updateEnemiesAndCombat(const float& dt);
};

