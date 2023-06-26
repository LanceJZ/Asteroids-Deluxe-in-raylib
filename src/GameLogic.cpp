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

	EM.AddLineModel(ThePlayer);
	EM.AddLineModel(ThePlayer->Flame);

	RC.Initialize();
	RC.SetCMRef(CM);
	RC.SetEMRef(EM);
	RC.SetComRef(Com);
}

void GameLogic::Load()
{
	ThePlayer->SetModel(CM.LoadAndGetLineModel("PlayerShip"));
	ThePlayer->Flame->SetModel(CM.LoadAndGetLineModel("PlayerFlame"));

	size_t rockModels[4];

	rockModels[0] = CM.LoadTheLineModel("RockOne");
	rockModels[1] = CM.LoadTheLineModel("RockTwo");
	rockModels[2] = CM.LoadTheLineModel("RockThree");
	rockModels[3] = CM.LoadTheLineModel("RockFour");

	RC.SetRockModels(rockModels);
}

bool GameLogic::BeginRun()
{
	EM.BeginRun();

	RC.NewGame();

	return true;
}

void GameLogic::Input()
{
	EM.Input();
}

void GameLogic::Update(float deltaTime)
{
	EM.Update(deltaTime);
}

void GameLogic::Draw3D()
{
	EM.Draw();
}

void GameLogic::Draw2D()
{
}
