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

	float perH = 42.75f;
	float perW = 42.75f;
	float playScreenW = windowWidth / perW;
	float playScreenH = windowHeight / perH;

	playerClear.Radius = 10.0f;
	playerClear.Enabled = false;
	player = new Player(playScreenW, playScreenH);

	return false;
}

bool Game::Load()
{
	playerShipModel = LoadModel("models/playership.obj");
	playerShipModel.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
		LoadTexture("models/playership.png");
	Model playerFlame = LoadModel("models/playerflame.obj");
	playerFlame.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
		LoadTexture("models/playerflame.png");
	Model shot = LoadModel("models/shot.obj");
	shot.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture =
		LoadTexture("models/shot.png");

	player->LoadModel(playerShipModel, shot, playerFlame);

	return 0;
}

bool Game::BeginRun()
{

	return false;
}

void Game::ProcessInput()
{
	if (player->Enabled)
	{
		player->Input();
	}
	else if (IsKeyPressed(KEY_N))
	{
		player->NewGame();
		//rockControl->NewGame();
		//theUFOControl->NewGame();
		//PlayerShipDisplay();
		//highscores->gameOver = false;
	}

	if (IsKeyPressed(KEY_PAUSE) && !player->gameOver)
	{
		player->paused = !player->paused;
	}
}


void Game::Update(float deltaTime)
{
	if (player->paused)
	{
		return;
	}

	UpdateCamera(&camera);

	player->Update(deltaTime);

}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(camera);
	//3D Drawing here.
	player->Draw();

	EndMode3D();
	//2D drawing, fonts go here.

	EndDrawing();
}

void Game::CheckPlayerClear()
{
	bool clear = true;

	//for (auto rock : rockControl->rocks)
	//{
	//	if (playerClear.CirclesIntersect(rock))
	//	{
	//		clear = false;
	//	}

	//	if (playerClear.CirclesIntersect(theUFOControl->ufo))
	//	{
	//		clear = false;
	//	}

	//	if (playerClear.CirclesIntersect(theUFOControl->ufo->shot))
	//	{
	//		clear = false;
	//	}
	//}

	if (clear)
	{
		player->Reset();
	}
}


void Game::Shutdown()
{
	CloseWindow();
	CloseAudioDevice();
}