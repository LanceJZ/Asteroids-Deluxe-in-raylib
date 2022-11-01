#include "WedgeControl.h"

WedgeControl::WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo)
{
	GameScreenWidth = playScreenW;
	GameScreenHeight = playScreenH;
	WedgeControl::player = player;

	wedgeGroup = new WedgeGroup(playScreenW, playScreenH, player, ufo);
}

WedgeControl::~WedgeControl()
{
}

bool WedgeControl::Initialise()
{
	wedgeGroup->Position = { 15, 15, 0 };
	wedgeGroup->Velocity.x = 2;
	wedgeGroup->Velocity.y = 1;

	wedgeGroup->Initialize();

	return false;
}

void WedgeControl::Load()
{

}

void WedgeControl::LoadModel(string model)
{
	wedgeGroup->LoadModel(model);
}

void WedgeControl::Input()
{

}

void WedgeControl::Update(float deltaTime)
{
	wedgeGroup->Update(deltaTime);
}

void WedgeControl::Draw()
{
	wedgeGroup->Draw();
}

void WedgeControl::Disperse()
{
}

void WedgeControl::SpawnGroup()
{
}
