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
	wedgeGroup->Position = { 10, 10, 0 };
	wedgeGroup->Velocity.x = 3;
	wedgeGroup->Velocity.y = 2;

	wedgeGroup->Initialise();

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
