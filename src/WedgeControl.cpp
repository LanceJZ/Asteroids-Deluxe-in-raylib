#include "WedgeControl.h"

WedgeControl::WedgeControl()
{
}

WedgeControl::~WedgeControl()
{
}

void WedgeControl::SetRef(CrossCom* cc, Managers* man, Player* player, UFO* ufo)
{
	CC = cc;
	Man = man;
	ThePlayer = player;
	TheUFO = ufo;

	TheWedgeGroup->SetRefs(cc, man, player, ufo);
}

bool WedgeControl::Initialise()
{
	//SpawnTimer->Reset(3);
	ready = false;

	return false;
}

void WedgeControl::SetModelID(size_t modelID)
{
	TheWedgeGroup->SetModelID(modelID);
}

void WedgeControl::Update(float deltaTime)
{
	if (!CC->SpawnWedgeGroup)
	{
		//SpawnTimer->Reset();
		return;
	}

	if (TheWedgeGroup->Enabled)
	{
		//SpawnTimer->Reset();
		return;
	}

	bool resetTimer = false;

	for (auto wedgePair : TheWedgeGroup->WedgePairs)
	{
		for (auto wedge : wedgePair->Wedges)
		{
			if (wedge->Enabled)
			{
				resetTimer = true;
			}
		}
	}

	if (resetTimer)
	{
		//SpawnTimer->Reset();
		return;
	}

	//if (SpawnTimer->Elapsed())
	//{
	//	SpawnTimer->Reset();

	//	if (ready)
	//	{
	//		SpawnGroup();
	//	}
	//	else if (!ready)
	//	{
	//		ready = true;
	//	}
	//}
}

void WedgeControl::SpawnGroup()
{
	//if (!ThePlayer->GameOver)
	//	PlaySound(SpawnSoundID);

	ready = false;

	TheWedgeGroup->Spawn();
}
