#include "WedgeControl.h"

WedgeControl::WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo, CrossCom* crosscom)
{
	GameScreenWidth = playScreenW;
	GameScreenHeight = playScreenH;
	WedgeControl::player = player;
	WedgeControl::crossCom = crosscom;
	spawnTimer = new Timer();
	wedgeGroup = new WedgeGroup(playScreenW, playScreenH, player, ufo, crossCom);
}

WedgeControl::~WedgeControl()
{
	UnloadSound(spawn);
}

bool WedgeControl::Initialise()
{
	wedgeGroup->Initialize();
	spawnTimer->Reset(3);
	ready = false;

	return false;
}

void WedgeControl::LoadSound(Sound explode, Sound spawn)
{
	WedgeControl::spawn = spawn;
	wedgeGroup->LoadSound(explode);
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

	if (!crossCom->spawnWedgeGroup)
	{
		spawnTimer->Reset();
		return;
	}

	if (wedgeGroup->Enabled)
	{
		spawnTimer->Reset();
		return;
	}

	bool resetTimer = false;

	for (auto wedgePair : wedgeGroup->wedgePairs)
	{
		for (auto wedge : wedgePair->wedges)
		{
			if (wedge->Enabled)
			{
				resetTimer = true;
			}
		}
	}

	if (resetTimer)
	{
		spawnTimer->Reset();
		return;
	}

	if (spawnTimer->Elapsed())
	{
		spawnTimer->Reset();

		if (ready)
		{
			SpawnGroup();
		}
		else if (!ready)
		{
			ready = true;
		}
	}
}

void WedgeControl::Draw()
{
	wedgeGroup->Draw();
}

void WedgeControl::SpawnGroup()
{
	if (!player->gameOver)
		PlaySound(spawn);

	ready = false;

	wedgeGroup->Spawn({ GameScreenWidth,
		GetRandomFloat(-GameScreenHeight, GameScreenHeight), 0}, GetRandomVelocity(1.5f));
}
