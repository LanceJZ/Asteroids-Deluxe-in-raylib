#pragma once
#include <memory>
#include "raylib.h"
#include "Managers.h"
#include "Player.h"
#include "RockControl.h"
#include "UFOControl.h"

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
	void Shutdown();


private:
	Player* ThePlayer;
	RockControl* RC;
	UFOControl* UC;
	CrossCom CC;
	Managers Man;

	void NewGame();
	void Draw3D();
	void Draw2D();
};

