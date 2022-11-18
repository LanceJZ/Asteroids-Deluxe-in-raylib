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
}

bool WedgeControl::Initialise()
{
	wedgeGroup->Initialize();
	spawnTimer->Reset(3);
	ready = false;

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
	spawnTimer->Update(deltaTime);

	if (spawnTimer->Elapsed())
	{
		spawnTimer->Reset();

		if (wedgeGroup->Enabled)
			return;

		if (crossCom->rocksUnderFour && ready)
		{
			SpawnGroup();
		}
		else if (!ready)
		{
			ready = true;
		}
	}

	if (!crossCom->rocksUnderFour)
	{
		spawnTimer->Reset();
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
	}

	wedgeGroup->Update(deltaTime);
}

void WedgeControl::Draw()
{
	wedgeGroup->Draw();
}

void WedgeControl::SpawnGroup() //TODO: See why not spawning a third time.
{
	ready = false;

	wedgeGroup->Spawn({ GameScreenWidth,
		GetRandomFloat(-GameScreenHeight, GameScreenHeight), 0}, GetRandomVelocity(3));
}
