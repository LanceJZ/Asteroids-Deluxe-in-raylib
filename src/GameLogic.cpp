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
}

void GameLogic::Load()
{
	ThePlayer->SetModel(CM.LoadAndGetLineModel("PlayerShip"));
	ThePlayer->Flame->SetModel(CM.LoadAndGetLineModel("PlayerFlame"));
}

bool GameLogic::BeginRun()
{
	EM.BeginRun();

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
