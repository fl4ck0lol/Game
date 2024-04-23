#include "stdafx.h"
#include"Game.h"
#include<SFML/Graphics.hpp>

int main()
{
    srand(time(nullptr));

    Game game;

    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    game.run();

    return 0;
}

