#pragma once
#include "State.h"
#include "GUI.h"
#include "GameState.h"
#include "PauseMenu.h"
#include"TileMap.h"

class State;
class PauseMenu;
class TileMap;

class EditorState :
    public State
{
public:
    

private:

    sf::View mainView;
    float cameraSpeed;

    short unsigned pressOnce;

    bool showSidebar;

    sf::Text cursorText;

    sf::Font font;
    std::map<std::string, Button*> buttons;

    std::map<std::string, Button*> sideBarButtons;

    PauseMenu* pausemenu;

    void InitialiseVars();
    void InitialiseKeyBinds();
    void InitialiseFonts();
    void InitialiseText();
    void IntitialiseButtons();
    void InitialiseBackGround();
    void InitialisePauseMenu();
    void InitialiseTileMap();
    void InitialiseGUI();

    short unsigned lastState;

    Button* gameState_button;

    TileMap* tileMap;

    sf::RectangleShape selector;
    sf::RectangleShape sideBar;

    sf::IntRect textureRect;

    TextureSelector* textureSelector;

    bool collision;
    short type;

public:
    EditorState(StateData* stateData);
    virtual ~EditorState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);
    void renderSideBarButtons(sf::RenderTarget& target);
    void updatePauseMenuButtons();
    void updateGUI();
    void renderGUI(sf::RenderTarget& target);
    void updateTile(const float& dt);
    void updateSideBarButtons();
};

