#include "GameLogic.h"

GameLogic::GameLogic()
{
	ThePlayer = std::make_shared<Player>();
	ThePlayer->Flame = std::make_shared<LineModel>();
}

GameLogic::~GameLogic()
{
}

void GameLogic::Initialize(Camera &camera)
{
	TheCamera = camera;

	ThePlayer->Flame->SetParent(ThePlayer);
	ThePlayer->SetManagerRef(Man);

	Man.EM.AddLineModel(ThePlayer);
	Man.EM.AddLineModel(ThePlayer->Flame);

	for (int i = 0; i < 4; i++)
	{
		ThePlayer->Shots.push_back(std::make_shared<Shot>());
		Man.EM.AddLineModel(ThePlayer->Shots[i]);
		ThePlayer->Shots[i]->SetManagerRef(Man);
	}

	RC.SetManagerRef(Man);
	ThePlayer->SetManagerRef(Man);

	RC.Initialize();
	RC.SetReferences(CC, ThePlayer);
}

void GameLogic::Load()
{
	ThePlayer->SetModel(Man.CM.LoadAndGetLineModel("PlayerShip"));
	ThePlayer->Flame->SetModel(Man.CM.LoadAndGetLineModel("PlayerFlame"));

	size_t shotModelID = Man.CM.LoadTheLineModel("Dot");

	for (int i = 0; i < 4; i++)
	{
		ThePlayer->Shots[i]->SetModel(Man.CM.GetLineModel(shotModelID));
	}

	size_t rockModels[4];

	rockModels[0] = Man.CM.LoadTheLineModel("RockOne");
	rockModels[1] = Man.CM.LoadTheLineModel("RockTwo");
	rockModels[2] = Man.CM.LoadTheLineModel("RockThree");
	rockModels[3] = Man.CM.LoadTheLineModel("RockFour");

	RC.SetRockModels(rockModels);

	size_t ufoModelID = Man.CM.LoadTheLineModel("UFO");


	size_t wedgeModelID = Man.CM.LoadTheLineModel("Wedge");
}

bool GameLogic::BeginRun()
{
	Man.EM.BeginRun(); //Any Entities added after this point need this method fired manually.

	RC.NewGame();

	return true;
}

void GameLogic::Input()
{
	Man.EM.Input();

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

	if (IsGamepadAvailable(0) && !ThePlayer->GameOver)
	{
		if (IsGamepadButtonPressed(0, 13)) //Menu Button
		{
			ThePlayer->Paused = !ThePlayer->Paused;
		}

		if (IsGamepadButtonPressed(0, 8)) //X button
		{
			MuteBackgroundMusic = !MuteBackgroundMusic;
		}
	}


	if (IsKeyPressed(KEY_P) && !ThePlayer->GameOver)
	{
		ThePlayer->Paused = !ThePlayer->Paused;
	}

	if (IsKeyPressed(KEY_D) && !ThePlayer->GameOver)
	{
		ThePlayer->Debug = true;
		RC.Debug(true);
		//UC.Debug(true);

	}

	if (IsKeyPressed(KEY_M))
	{
		MuteBackgroundMusic = !MuteBackgroundMusic;
	}
}

void GameLogic::Update(float deltaTime)
{
	Man.EM.Update(deltaTime);
	RC.Update(deltaTime);
}

void GameLogic::Draw3D()
{
	Man.EM.Draw();
}

void GameLogic::Draw2D()
{
}

void GameLogic::NewGame()
{
	//ThePlayer->NewGame();
	//RC.NewGame();
	//UC.NewGame();
	//PlayerShipDisplay();
	//HS.GameOver = false;
}
