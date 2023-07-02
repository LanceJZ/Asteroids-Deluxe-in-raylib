#include "GameLogic.h"

GameLogic::GameLogic()
{
	UC = std::make_shared<UFOControl>();
	RC = std::make_shared<RockControl>();
	ThePlayer = std::make_shared<Player>();
	ThePlayer->Flame = std::make_shared<LineModel>();
	UC->TheUFO = std::make_shared<UFO>();
	UC->TheUFO->TheShot = std::make_shared<Shot>();
}

GameLogic::~GameLogic()
{
}

void GameLogic::Initialize(Camera &camera)
{
	TheCamera = camera;

	ThePlayer->Flame->SetParent(ThePlayer);
	ThePlayer->SetManagersRef(Man);

	Man.EM.AddCommon(RC);
	Man.EM.AddCommon(UC);
	Man.EM.AddLineModel(ThePlayer);
	Man.EM.AddLineModel(ThePlayer->Flame);
	Man.EM.AddLineModel(UC->TheUFO);

	for (int i = 0; i < 4; i++)
	{
		ThePlayer->Shots.push_back(std::make_shared<Shot>());
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

	ThePlayer->SetManagersRef(Man);
}

void GameLogic::Load()
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
}

bool GameLogic::BeginRun()
{
	Man.EM.BeginRun(); //Any Entities added after this point need this method fired manually.

	NewGame();

	State = InPlay;

	return true;
}

void GameLogic::Input()
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

void GameLogic::Update(float deltaTime)
{
	if (State == Pause)
		return;

	Man.EM.Update(deltaTime);
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
	ThePlayer->NewGame();
	RC->NewGame();
	UC->NewGame();
	//HS.GameOver = false;
}
