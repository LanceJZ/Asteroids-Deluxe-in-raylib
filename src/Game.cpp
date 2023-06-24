#include "Game.h"

bool Game::Initialize(Camera &camera) //Initialize
{
	TheCamera = camera;
	TheGameLogic.Initialize(camera);
	SetTargetFPS(60);
	SetWindowTitle("Asteroids Deluxe");

	return true;
}

bool Game::Load()
{
	TheGameLogic.Load();
	return true;
}

bool Game::BeginRun()
{
	TheGameLogic.BeginRun();
	return true;
}

void Game::ProcessInput()
{
	TheGameLogic.Input();
}


void Game::Update(float deltaTime)
{
	TheGameLogic.Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(TheCamera);

	//3D Drawing here.
	TheGameLogic.Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.
	TheGameLogic.Draw2D();
	DrawFPS(5, 5);

	EndDrawing();
}

void Game::Shutdown()
{
}