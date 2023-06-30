#pragma once
#include <memory>
#include "Managers.h"
#include "Player.h"
#include "RockControl.h"

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

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	std::shared_ptr<Player> ThePlayer;
	std::shared_ptr<RockControl> RC;
	CrossCom CC;
	Managers Man;

	void NewGame();
};
