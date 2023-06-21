#pragma once
#include <memory>
#include "LineModel.h"
#include "ContentManager.h"
#include "EntityManager.h"
#include "Player.h"

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
	GameLogic();
	virtual ~GameLogic();

	void Initialize();
	void Load();
	bool BeginRun();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw3D();
	virtual void Draw2D();

private:
	std::shared_ptr<Player> ThePlayer;

	ContentManager Content;
	EntityManager Entities;
};