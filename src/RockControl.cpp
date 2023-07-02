#include "RockControl.h"

RockControl::RockControl()
{
}

RockControl::~RockControl()
{
	RockRefs.clear();
}

bool RockControl::Initialize()
{

	return false;
}

void RockControl::SetManagersRef(Managers& man)
{
	Man = &man;
}

void RockControl::SetCrossRef(CrossCom& com)
{
	CC = &com;
}

void RockControl::SetUFORef(UFO* ufo)
{
	TheUFO = ufo;
}

void RockControl::SetPlayerRef(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

void RockControl::SetSoundID(size_t explodeID)
{
	ExplodeSoundID = explodeID;
}

void RockControl::SetRockModels(size_t rockModelRefs[4])
{
	std::copy(rockModelRefs, rockModelRefs + 4, RockModelRefs);
}

void RockControl::Update()
{
	if (CC->RockHit)
	{
		RockHit();
	}

	if (TheUFO->Enabled)
	{
		for (size_t i = 0; i < RockRefs.size(); i++)
		{
			if (RockRefs[i]->Enabled)
			{
				CC->RockData[i].Position = RockRefs[i]->Position;
				CC->RockData[i].Velocity = RockRefs[i]->Velocity;
				CC->RockData[i].Enabled = RockRefs[i]->Enabled;
			}
		}
	}
}

void RockControl::NewGame()
{
	NewRockCount = 4;
	NewWave();
}

void RockControl::NewWave()
{
	CC->NewWave = true;
	CC->SpawnWedgeGroup = false;

	SpawnRocks({ 0, 0, 0 }, NewRockCount, Rock::Large);

	if (NewRockCount < 12)
		NewRockCount++;
}

void RockControl::Debug(bool debugOn)
{
	for (auto rock : RockRefs)
	{
		rock->Debug = true;
	}
}

void RockControl::SpawnRocks(Vector3 pos, int count, Rock::RockSize size)
{
	for (int rock = 0; rock < count; rock++)
	{
		bool spawnNewRock = true;
		size_t rockNumber = RockRefs.size();

		for (size_t rockCheck = 0; rockCheck < rockNumber; rockCheck++)
		{
			if (!RockRefs[rockCheck]->Enabled)
			{
				spawnNewRock = false;
				rockNumber = rockCheck;
				break;
			}
		}

		if (spawnNewRock)
		{
			size_t rockType = GetRandomValue(0, 3);
			RockRefs.push_back(new Rock());
			CC->RockData.push_back({});
			Man->EM.AddLineModel(RockRefs[rockNumber]);
			RockRefs[rockNumber]->SetModel(Man->CM.GetLineModel(RockModelRefs[rockType]));
			RockRefs[rockNumber]->SetReferences(*CC, ThePlayer);
		}

		RockRefs[rockNumber]->Spawn(pos, size);
	}
}

void RockControl::RockHit()
{
	Vector3 pos = {};
	Rock::RockSize size = {};

	for (auto rock : RockRefs)
	{
		if (rock->BeenHit)
		{
			size = rock->Size;
			pos = rock->Position;
			rock->BeenHit = false;

			break;
		}
	}

	switch (size)
	{
	case Rock::Large:
		SpawnRocks(pos, 2, Rock::Medium);
		break;

	case Rock::Medium:
		SpawnRocks(pos, 2, Rock::Small);
		break;

	case Rock::Small:
		CheckEndOfWave();
		break;

	default:
		break;
	}
}

void RockControl::CheckEndOfWave()
{
	bool endOfWave = true;

	for (auto rock : RockRefs)
	{
		if (rock->Enabled)
		{
			endOfWave = false;
			break;
		}
	}

	if (endOfWave)
	{
		NewWave();
	}
}