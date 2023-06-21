#include "Game.h"
#include "raymath.h"
#include <string>

Game::Game()
{

}

Game::~Game()
{

}

void Game::GameLoop()
{
	while (!WindowShouldClose())
	{
		ProcessInput();
		Update(GetFrameTime());
		Draw();
	}

	Shutdown();
}

bool Game::Initialize() //Initialize
{
	int windowHeight = 960; //height
	int windowWidth = 1280; //width

	InitWindow(windowWidth, windowHeight, "Game");
	InitAudioDevice();
	SetTargetFPS(60);

	Image icon = LoadImage("icon.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	// Define the camera to look into our 3D world
	TheCamera.position = { 0.0f, 0.0f, -50.0f };  // Camera position
	TheCamera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	TheCamera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	TheCamera.fovy = (float)GetScreenHeight();		//Camera/World space is screen space.
	TheCamera.projection = CAMERA_ORTHOGRAPHIC;   // Camera mode type

	TheGameLogic.Initialize();

	return false;
}

bool Game::Load()
{
	TheGameLogic.Load();
	return 0;
}

bool Game::BeginRun()
{
	TheGameLogic.BeginRun();
	return false;
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

	EndDrawing();
}

void Game::Shutdown()
{
	CloseWindow();
	CloseAudioDevice();
}