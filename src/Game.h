#pragma once
#include "raylib.h"
#include "GameLogic.h"

class Game
{
public:
	Camera TheCamera = { 0 };

	bool Initialize(Camera &camera);
	bool Load();
	bool BeginRun();
	void ProcessInput();
	void Update(float deltaTime);
	void Draw();
	void Shutdown();

private:
	GameLogic TheGameLogic;
};

