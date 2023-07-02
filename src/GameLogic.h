#pragma once
#include <memory>
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

class GameLogic
{
public:
	GameState State = MainMenu;
	Camera TheCamera = { 0 };

	GameLogic();
	virtual ~GameLogic();

	bool MuteBackgroundMusic;
	void Initialize(Camera &camera);
	void Load();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw3D();
	void Draw2D();

private:
	std::shared_ptr<Player> ThePlayer;
	std::shared_ptr<RockControl> RC;
	std::shared_ptr<UFOControl> UC;
	CrossCom CC;
	Managers Man;

	void NewGame();
};
