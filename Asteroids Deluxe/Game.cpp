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
	ufoControl = new UFOControl(playScreenW, playScreenH, player);
	rockControl = new RockControl(playScreenW, playScreenH, player, ufoControl->ufo);


	return false;
}

bool Game::Load()
{
	string rockOne = "Models/RockOne.vec";
	string rockTwo = "Models/RockTwo.vec";
	string rockThree = "Models/RockThree.vec";
	string rockFour = "Models/RockFour.vec";

	player->LoadModel("Models/PlayerShip.vec", "Models/PlayerFlame.vec");
	rockControl->LoadModel(rockOne, rockTwo, rockThree, rockFour);
	ufoControl->LoadModel("Models/UFO.vec");

	return 0;
}

bool Game::BeginRun()
{
	player->Initialise();
	ufoControl->Initialise();
	rockControl->Initialise();
	rockControl->NewGame();

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
		rockControl->NewGame();
		ufoControl->NewGame();
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
	rockControl->Update(deltaTime);
	ufoControl->Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(camera);
	//3D Drawing here.
	player->Draw();
	rockControl->Draw();
	ufoControl->Draw();

	EndMode3D();
	//2D drawing, fonts go here.

	EndDrawing();
}

void Game::CheckPlayerClear()
{
	bool clear = true;

	for (auto rock : rockControl->rocks)
	{
		if (playerClear.CirclesIntersect(rock))
		{
			clear = false;
		}

		if (playerClear.CirclesIntersect(ufoControl->ufo))
		{
			clear = false;
		}

		if (playerClear.CirclesIntersect(ufoControl->ufo->shot))
		{
			clear = false;
		}
	}

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