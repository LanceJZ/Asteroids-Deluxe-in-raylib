#include "raylib.h"
#include "Game.h"

int main()
{
    Game game;

    game.Initialise();
    game.Load();
    game.BeginRun();
    game.GameLoop();
    game.Shutdown();
}