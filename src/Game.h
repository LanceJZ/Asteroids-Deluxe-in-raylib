#pragma once
#include <memory>
#include "raylib.h"
#include "Managers.h"
#include "Player.h"
#include "RockControl.h"
#include "UFOControl.h"
#include "WedgeControl.h"

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
	virtual ~Game();

	bool MuteBackgroundMusic;
	GameState State = MainMenu;
	Camera TheCamera = { 0 };

	bool Initialize(Camera &camera);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();

private:
	Player* ThePlayer;
	RockControl* RC;
	UFOControl* UC;
	WedgeControl* WC;
	CrossCom CC;
	Managers Man;

	void NewGame();
	void Draw3D();
	void Draw2D();
};

