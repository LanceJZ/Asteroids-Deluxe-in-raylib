#include "GameLogic.h"

GameLogic::GameLogic()
{
}

GameLogic::~GameLogic()
{
}

void GameLogic::Initialize()
{
	ThePlayer = std::make_shared<Player>();
	ThePlayer->Flame = std::make_shared<LineModel>();
	ThePlayer->Flame->AddParent(ThePlayer);

	EM.AddLineModel(ThePlayer);
	EM.AddLineModel(ThePlayer->Flame);

	EM.Initialize();
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
