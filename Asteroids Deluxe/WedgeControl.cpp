#include "WedgeControl.h"

WedgeControl::WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo)
{
	GameScreenWidth = playScreenW;
	GameScreenHeight = playScreenH;
	WedgeControl::player = player;
	spawnTimer = new Timer();
	wedgeGroup = new WedgeGroup(playScreenW, playScreenH, player, ufo);
}

WedgeControl::~WedgeControl()
{
}

bool WedgeControl::Initialise()
{
	wedgeGroup->Initialize();
	spawnTimer->Reset(3);

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
	spawnTimer->Update(deltaTime);

	if (spawnTimer->Elapsed())
	{
		SpawnGroup();
	}
}

void WedgeControl::Draw()
{
	wedgeGroup->Draw();
}

void WedgeControl::SpawnGroup()
{

}
