#include "Game.h"

Game::Game()
{
	UC = new UFOControl();
	RC = new RockControl();
	WC = new WedgeControl();
	ThePlayer = new Player();
	ThePlayer->Flame = new LineModel();
	UC->TheUFO = new UFO();
	UC->TheUFO->TheShot = new Shot();
}

Game::~Game()
{
}

bool Game::Initialize(Camera &camera) //Initialize
{
	TheCamera = camera;

	SetTargetFPS(60);
	SetWindowTitle("Asteroids Deluxe");

	ThePlayer->Flame->SetParent(ThePlayer);
	ThePlayer->SetManagersRef(Man);

	Man.EM.AddCommon(RC);
	Man.EM.AddCommon(UC);
	Man.EM.AddCommon(WC);
	Man.EM.AddLineModel(ThePlayer);
	Man.EM.AddLineModel(ThePlayer->Flame);
	Man.EM.AddLineModel(UC->TheUFO);
	Man.EM.AddLineModel(UC->TheUFO->TheShot);

	for (int i = 0; i < 4; i++)
	{
		ThePlayer->Shots.push_back(new Shot());
		Man.EM.AddLineModel(ThePlayer->Shots[i]);
		ThePlayer->Shots[i]->SetManagersRef(Man);
	}

	RC->SetManagersRef(Man);
	RC->SetPlayerRef(ThePlayer);
	RC->SetUFORef(UC->TheUFO);
	RC->SetCrossRef(CC);

	UC->SetManagersRef(Man);
	UC->SetPlayerRef(ThePlayer);
	UC->SetCrossRef(CC);

	WC->SetRef(&CC, &Man, ThePlayer, UC->TheUFO);

	ThePlayer->SetManagersRef(Man);

	return true;
}

bool Game::Load()
{
	size_t shotModelID = Man.CM.LoadTheLineModel("Dot");
	ThePlayer->SetShipModelID(Man.CM.LoadTheLineModel("PlayerShip"));
	ThePlayer->Flame->SetModel(Man.CM.LoadAndGetLineModel("PlayerFlame"));
	ThePlayer->SetShotModelID(shotModelID);

	size_t rockModels[4];

	rockModels[0] = Man.CM.LoadTheLineModel("RockOne");
	rockModels[1] = Man.CM.LoadTheLineModel("RockTwo");
	rockModels[2] = Man.CM.LoadTheLineModel("RockThree");
	rockModels[3] = Man.CM.LoadTheLineModel("RockFour");

	RC->SetRockModels(rockModels);

	UC->TheUFO->SetModel(Man.CM.GetLineModel(Man.CM.LoadTheLineModel("UFO")));
	UC->TheUFO->TheShot->SetModel(Man.CM.GetLineModel(shotModelID));

	size_t wedgeModelID = Man.CM.LoadTheLineModel("Wedge");
	WC->SetModelID(wedgeModelID);

	return true;
}

bool Game::BeginRun()
{
	Man.EM.BeginRun(); //Any Entities added after this point need this method fired manually.

	NewGame();

	State = InPlay;

	return true;
}

void Game::ProcessInput()
{
	Man.EM.Input();

	if (State == MainMenu)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 15))//Start button
			{
				NewGame();
			}
		}

		if (IsKeyPressed(KEY_N))
		{
			NewGame();
		}

		if (IsKeyPressed(KEY_D))
		{
			ThePlayer->Debug = true;
			RC->Debug(true);
			//UC.Debug(true);

		}
	}

	if (State == InPlay)
	{
		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = Pause;
			}

			if (IsGamepadButtonPressed(0, 8)) //X button
			{
				MuteBackgroundMusic = !MuteBackgroundMusic;
			}
		}

		if (IsKeyPressed(KEY_M))
		{
			MuteBackgroundMusic = !MuteBackgroundMusic;
		}


		if (IsKeyPressed(KEY_P))
		{
			State = Pause;
		}
	}
	else if (State == Pause)
	{
		if (IsKeyPressed(KEY_P))
		{
			State = InPlay;
		}

		if (IsGamepadAvailable(0))
		{
			if (IsGamepadButtonPressed(0, 13)) //Menu Button
			{
				State = InPlay;
			}
		}
	}
}


void Game::Update(float deltaTime)
{
	if (State == Pause)
		return;

	Man.EM.Update(deltaTime);
}

void Game::Draw()
{
	BeginDrawing();
	ClearBackground({ 8, 2, 16, 100 });
	BeginMode3D(TheCamera);

	//3D Drawing here.
	Draw3D();

	EndMode3D();

	//2D drawing, fonts go here.

	Draw2D();
#ifdef _DEBUG
	DrawFPS(5, 5);
#endif

	EndDrawing();
}

void Game::Shutdown()
{
}

void Game::NewGame()
{
	ThePlayer->NewGame();
	RC->NewGame();
	UC->NewGame();
	WC->SpawnGroup();
	//HS.GameOver = false;
}

void Game::Draw3D()
{
	Man.EM.Draw();
}

void Game::Draw2D()
{
}
