#pragma once
#include "raylib.h"
#include <vector>
#include "Player.h"
#include "RockControl.h"
#include "UFOControl.h"
#include "WedgeControl.h"
#include "HighScore.h"
#include "CrossCom.h"
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
	Color color{ 160, 160, 255, 255 };
	Model playerShipModel;
	Entity playerClear;
	Player* player;
	RockControl* rockControl;
	UFOControl* ufoControl;
	WedgeControl* wedgeControl;
	CrossCom* crossCom;
	HighScore* highscores;
	vector<LineModel*> playerShips;

	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

	void PlayerShipDisplay();
	void CheckPlayerClear();
};

