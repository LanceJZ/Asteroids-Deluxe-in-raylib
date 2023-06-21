#include "raylib.h"
#include "Game.h"

int main()
{
    static Game game;

    game.Initialize();
    game.Load();
    game.BeginRun();
    game.GameLoop();
}