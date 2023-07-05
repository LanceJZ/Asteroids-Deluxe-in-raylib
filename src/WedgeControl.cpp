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

	WG = new WedgeGroup();
	man->EM.AddEntity(WG);
	WG->SetRefs(cc, man, player, ufo);

	//for (auto wedgePairs : WG->WedgePairs)
	//{
	//	for (auto wedge : wedgePairs->Wedges)
	//	{
	//		wedge->SetParent(wedgePairs);
	//	}

	//	wedgePairs->SetParent(WG);
	//}
}

bool WedgeControl::Initialize()
{
	//SpawnTimer->Reset(3);
	ready = false;

	return false;
}

void WedgeControl::SetModelID(size_t modelID)
{
	WG->SetModelID(modelID);
}

void WedgeControl::Update()
{
	Common::Update();

	if (!CC->SpawnWedgeGroup)
	{
		//SpawnTimer->Reset();
		return;
	}

	if (WG->Enabled)
	{
		//SpawnTimer->Reset();
		return;
	}

	bool resetTimer = false;

	for (auto wedgePair : WG->WedgePairs)
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

	WG->Spawn();
}
