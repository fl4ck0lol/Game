#pragma once
#include "State.h"
#include "GameState.h"
#include "GUI.h"
#include "EditorState.h"
#include "SettingsState.h"
using namespace GUI;

class MainMenuState :
    public State
{
private:
    sf::RectangleShape Background;
    sf::RectangleShape container;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    void InitialiseKeyBinds();
    void InitialiseFonts();
    void IntitialiseButtons();
    void InitialiseBackGround();

    const int centerButtons(float button_x);

    Button* gameState_button; 

public:
    MainMenuState(StateData* stateData);
    virtual ~MainMenuState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void updateButtons();
    void renderButtons(sf::RenderTarget& target);
};

