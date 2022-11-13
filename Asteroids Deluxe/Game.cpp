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

	float per = 42.75f;
	float playScreenW = windowWidth / per;
	float playScreenH = windowHeight / per;

	playerClear.Radius = 10.0f;
	playerClear.Enabled = false;
	player = new Player(playScreenW, playScreenH);
	ufoControl = new UFOControl(playScreenW, playScreenH, player);
	crossCom = new CrossCom();
	rockControl = new RockControl(playScreenW, playScreenH, player, ufoControl->ufo, crossCom);
	wedgeControl = new WedgeControl(playScreenW, playScreenH, player, ufoControl->ufo, crossCom);

	highscores = new HighScore();
	highscores->Load();
	player->highScore = highscores->highScore;

	return false;
}

bool Game::Load()
{
	string rockOne = "Models/RockOne.vec";
	string rockTwo = "Models/RockTwo.vec";
	string rockThree = "Models/RockThree.vec";
	string rockFour = "Models/RockFour.vec";
	LineModel dotModel;
	dotModel.LoadModel("Models/Dot.vec");

	player->LoadModel("Models/PlayerShip.vec", "Models/PlayerFlame.vec",
		"Models/PlayerShield.vec", dotModel.GetModel());
	rockControl->LoadModel(rockOne, rockTwo, rockThree, rockFour, dotModel.GetModel());
	ufoControl->LoadModel("Models/UFO.vec", dotModel.GetModel());
	wedgeControl->LoadModel("Models/Wedge.vec");

	return 0;
}

bool Game::BeginRun()
{
	player->Initialize();
	ufoControl->Initialize();
	rockControl->Initialize();
	rockControl->NewGame();
	wedgeControl->Initialise();

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
		PlayerShipDisplay();
		highscores->gameOver = false;
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
	wedgeControl->Update(deltaTime);

	for (auto line : player->lines)
	{
		line->Update(deltaTime);
	}

	if (player->Enabled)
	{
		playerClear.Enabled = false;

		if (player->newLife)
		{
			player->newLife = false;
			PlayerShipDisplay();
		}
	}
	else
	{
		if (player->exploding)
		{
			bool done = true;

			for (auto line : player->lines)
			{
				if (line->Enabled)
				{
					done = false;
					return;
				}
			}

			if (done)
			{
				player->exploding = false;
			}
		}

		if (player->lives > 0)
		{
			playerClear.Enabled = true;
			rockControl->Update(deltaTime);
			CheckPlayerClear();
			PlayerShipDisplay();
		}
		else if (!player->gameOver)
		{
			PlayerShipDisplay();
			highscores->highScore = player->highScore;
			highscores->CheckForNewHighScore(player->score);
			player->gameOver = true;
			highscores->gameOver = true;
		}
		else
		{
			highscores->Update(deltaTime);
		}
	}
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
	wedgeControl->Draw();

	EndMode3D();
	//2D drawing, fonts go here.
	highscores->Draw();

	if (player->paused)
	{
		DrawText("Paused", (GetScreenWidth() / 2) - 80, (GetScreenHeight() / 2) - 20, 50, WHITE);
	}

	DrawText(const_cast<char*>(to_string(player->score).c_str()), 200, 5, 45, WHITE);
	DrawText(const_cast<char*>(to_string(player->highScore).c_str()), GetScreenWidth() / 2, 4, 20, WHITE);
	DrawText("(C) 1979 ATARI INC", (GetScreenWidth() / 2) - 15, GetScreenHeight() - 12, 8, WHITE);

	EndDrawing();
}

void Game::PlayerShipDisplay()
{
	float line = player->WindowHeight - player->Radius - 2.5f;
	float column = 20.0f;

	if (player->lives > playerShips.size())
	{
		playerShips.push_back(new LineModel());
		playerShips[playerShips.size() - 1]->SetModel(player->GetModel());
	}

	for (int i = 0; i < playerShips.size(); i++)
	{
		playerShips[i]->Y(line);
		playerShips[i]->X(column);
		playerShips[i]->RotationZ = PI / 2;
		playerShips[i]->Enabled = false;
		column += 1.125f;
	}

	for (int i = 0; i < player->lives; i++)
	{
		playerShips[i]->Enabled = true;
	}
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

		if (playerClear.CirclesIntersect(wedgeControl->wedgeGroup))
		{
			clear = false;
		}

		for (auto wedgePair : wedgeControl->wedgeGroup->wedgePairs)
		{
			if (playerClear.CirclesIntersect(wedgePair))
			{
				clear = false;
			}

			for (auto wedge : wedgePair->wedges)
			{
				if (playerClear.CirclesIntersect(wedge))
				{
					clear = false;
				}
			}
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