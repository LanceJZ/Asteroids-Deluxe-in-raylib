#pragma once
#include "raylib.h"
#include <vector>
using namespace std;

enum GameState
{
	PlayerHit,
	Over,
	InPlay,
	Pause,
	HighScores,
	MainMenu
};

class Game
{
public:
	Game();
	~Game();

	void GameLoop();
	bool Initialise();
	bool Load();
	bool BeginRun();
	void Shutdown();

	Camera camera = { 0 };


private:
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
};

