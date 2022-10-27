#pragma once
#include "raylib.h"
#include <vector>
#include "Player.h"
#include "RockControl.h"
#include "UFOControl.h"
#include "WedgeControl.h"
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
	Model playerShipModel;
	Entity playerClear;
	Player* player;
	RockControl* rockControl;
	UFOControl* ufoControl;
	WedgeControl* wedgeControl;

	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

	void CheckPlayerClear();

};

