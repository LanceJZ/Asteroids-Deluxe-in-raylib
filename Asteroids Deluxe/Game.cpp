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
}

bool Game::Initialise()
{
	int windowHeight = 960; //height
	int windowWidth = 1280; //width

	InitWindow(windowWidth, windowHeight, "Game");
	InitAudioDevice();
	SetTargetFPS(60);

	Image icon = LoadImage("icon-PKG_32x32.png");
	ImageFormat(&icon, PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	SetWindowIcon(icon);
	// Define the camera to look into our 3D world
	camera.position = { 0.0f, 0.0f, -50.0f };  // Camera position
	camera.target = { 0.0f, 0.0f, 0.0f };      // Camera looking at point
	camera.up = { 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
	camera.fovy = 45.0f;                       // Camera field-of-view Y
	camera.projection = CAMERA_ORTHOGRAPHIC;   // Camera mode type

	return false;
}

bool Game::Load()
{

	return 0;
}

bool Game::BeginRun()
{

	return false;
}

void Game::ProcessInput()
{

}


void Game::Update(float deltaTime)
{

}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(camera);

	//3D Drawing here.

	EndMode3D();
	//2D drawing, fonts go here.

	EndDrawing();
}

void Game::Shutdown()
{
	CloseWindow();
	CloseAudioDevice();
}