#pragma once
#include <memory>
#include "LineModel.h"
#include "ContentManager.h"
#include "EntityManager.h"
#include "Player.h"
#include "RockControl.h"
#include "CrossCom.h"

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
	Camera TheCamera = { 0 };

	GameLogic();
	virtual ~GameLogic();

	void Initialize(Camera &camera);
	void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	std::shared_ptr<Player> ThePlayer;

	ContentManager CM;
	EntityManager EM;
	CrossCom Com;
	RockControl RC;
};