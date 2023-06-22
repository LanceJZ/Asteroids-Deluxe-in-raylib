#pragma once
#include <string>
#include <vector>
#include "raylib.h"
#include "GameLogic.h"

class Game
{
public:
	Game();
	~Game();

	void GameLoop();
	bool Initialize();
	bool Load();
	bool BeginRun();

	Camera TheCamera = { 0 };


private:
	GameLogic TheGameLogic;

	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
	void Shutdown();
};

