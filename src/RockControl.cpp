 #include "RockControl.h"

bool RockControl::Initialize()
{

	return false;
}

void RockControl::SetEMRef(EntityManager& em)
{
	EM = &em;
}

void RockControl::SetCMRef(ContentManager& cm)
{
	CM = &cm;
}

void RockControl::SetComRef(CrossCom& com)
{
	Com = &com;
}

void RockControl::SetSound(Sound exp)
{
	Explode = exp;
}

void RockControl::SetRockModels(size_t rockModelRefs[4])
{
	std::copy(rockModelRefs, rockModelRefs + 4, RockModelRefs);

	//for (int i = 0; i < 4; i++)
	//{
	//	RockModelRefs[i] = rockModelRefs[i];
	//}
}

void RockControl::Update(float deltaTime)
{

}

void RockControl::NewGame(void)
{
	NewWave();
}

void RockControl::NewWave(void)
{
	Com->NewWave = true;
	Com->SpawnWedgeGroup = false;

	SpawnRocks({ 0, 0, 0 }, NewRockCount, Rock::Large);

	if (NewRockCount < 12)
		NewRockCount++;
}

void RockControl::SpawnRocks(Vector3 pos, int count, Rock::RockSize size)
{
	for (int rock = 0; rock < count; rock++)
	{
		bool spawnNewRock = true;
		size_t rockNumber = RocksIDs.size();

		for (size_t rockCheck = 0; rockCheck < rockNumber; rockCheck++)
		{
			if (!EM->LineModels[RocksIDs[rockCheck]].get()->Enabled)
			{
				spawnNewRock = false;
				rockNumber = rockCheck;
				break;
			}
		}

		if (spawnNewRock)
		{
			size_t rockType = GetRandomValue(0, 3);
			size_t rock = RocksIDs.size();
			RockRefs.push_back(std::make_shared<Rock>());
			RocksIDs.push_back(EM->AddLineModel(RockRefs[RockRefs.size() - 1]));
			EM->LineModels[RocksIDs[rock]].get()->SetModel(CM->GetLineModel(RockModelRefs[rockType]));
		}

		RockRefs[rockNumber]->Spawn(pos, size);
	}
}
