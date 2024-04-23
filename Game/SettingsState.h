#pragma once
#include "State.h"
#include "GUI.h"
using namespace GUI;

class SettingsState :
    public State
{
private:
    sf::Texture bgTexture;
    sf::RectangleShape Background;
    sf::RectangleShape container;
    sf::Font font;
    sf::Text settingsText;
    sf::RectangleShape textContainer;

    std::map<std::string, Button*> buttons;
    std::map<std::string, DropDownList*> dropDownButtons;

    sf::Text optionsText;
    std::vector<sf::VideoMode> vmodes;
    std::vector<bool> fullscreen_mode;
    std::vector<bool> vsync;

    void InitialiseKeyBinds();
    void InitialiseFonts();
    void IntitialiseButtons();
    const int centerButtons(float button_x);
    void InitialiseBackGround();

    void initialiseText();
    void initialiseVars();


public: 
    SettingsState(StateData* stateData);
    virtual ~SettingsState();

    void updateInput(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);
    void updateButtons(const float& dt);
    void renderButtons(sf::RenderTarget& target);
};

