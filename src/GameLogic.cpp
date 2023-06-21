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

	Entities.AddLineModel(ThePlayer);

	Entities.Initialize();
}

void GameLogic::Load()
{
	ThePlayer->SetModel(Content.LoadAndGetLineModel("PlayerShip"));
}

bool GameLogic::BeginRun()
{
	Entities.BeginRun();


	return true;
}

void GameLogic::Input()
{
	Entities.Input();
}

void GameLogic::Update(float deltaTime)
{
	Entities.Update(deltaTime);
}

void GameLogic::Draw3D()
{
	Entities.Draw();
}

void GameLogic::Draw2D()
{

}
