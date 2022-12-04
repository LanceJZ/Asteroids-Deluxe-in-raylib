 #include "RockControl.h"
#include <vector>

RockControl::RockControl(float screenWidth, float screenHeight, Player* player, UFO* ufo, CrossCom* crosscom)
{
	GameScreenWidth = screenWidth;
	GameScreenHeight = screenHeight;
	RockControl::player = player;
	RockControl::ufo = ufo;
	RockControl::crossCom = crosscom;
}

bool RockControl::Initialize()
{

	return false;
}

void RockControl::LoadModel(string modelOne, string modelTwo, string modelThree,
	string modelFour, vector<Vector3> dotModel)
{
	rockModels[0].LoadModel(modelOne);
	rockModels[1].LoadModel(modelTwo);
	rockModels[2].LoadModel(modelThree);
	rockModels[3].LoadModel(modelFour);

	RockControl::dotModel = dotModel;
}

void RockControl::LoadSound(Sound exp)
{
	Explode = exp;
}

void RockControl::Update(float deltaTime)
{
	bool rockHit = false;
	Rock* rockWasHit = NULL;

	for (auto rock : rocks)
	{
		if (rock->BeenHit)
		{
			rockHit = true;
			rockWasHit = rock;
			rockWasHit->BeenHit = false;
		}

		rock->Update(deltaTime);
	}

	for (int i = 0; i < rocks.size(); i++)
	{
		ufo->rocks[i]->Update(rocks[i]->Position, rocks[i]->Enabled);
	}

	if (rockHit)
	{
		RockHit(rockWasHit);
	}

	if (noRocks)
	{
		if (!ufo->Enabled)
		{
			NewWave();
			noRocks = false;
		}
	}
}

void RockControl::Draw(void)
{
	for (auto rock : rocks)
	{
		rock->Draw();
	}
}

void RockControl::NewGame(void)
{
	for (auto rock : rocks)
	{
		rock->Enabled = false;
	}

	newRockCount = 4;
	NewWave();
}

void RockControl::NewWave(void)
{
	crossCom->newWave = true;
	crossCom->spawnWedgeGroup = false;
	player->wave++;
	SpawnRocks({ 0, 0, 0 }, newRockCount, Rock::Large);


	if (newRockCount < 12)
		newRockCount++;
}

void RockControl::RockHit(Rock* rockHit)
{
	rockHit->exploder->Spawn(rockHit->Position, 15, rockHit->Radius);

	switch (rockHit->size)
	{
	case Rock::Large:
		SpawnRocks(rockHit->Position, 2, Rock::Medium);
		break;

	case Rock::Medium:
		SpawnRocks(rockHit->Position, 2, Rock::Small);
		break;

	case Rock::Small:
		bool rocksGone = true;

		for (auto rock: rocks)
		{
			if (rock->Enabled)
				rocksGone = false;
		}

		if (rocksGone)
			noRocks = true;
;
		break;
	}

	int activeRockCount = 0;

	for (auto rock : rocks)
	{
		if (rock->Enabled)
		{
			activeRockCount++;
		}
	}

	if (activeRockCount < (newRockCount - 1))
	{
		crossCom->spawnWedgeGroup = true;
	}
	else
	{
		crossCom->spawnWedgeGroup = false;
	}
}

void RockControl::SpawnRocks(Vector3 pos, int count, Rock::RockSize size)
{
	for (int rock = 0; rock < count; rock++)
	{
		bool spawnnewrock = true;
		int rockN = (int)rocks.size();
		float maxSpeed = 10.666f;

		for (int rockcheck = 0; rockcheck < rockN; rockcheck++)
		{
			if (!rocks[rockcheck]->Enabled)
			{
				spawnnewrock = false;
				rockN = rockcheck;
				break;
			}
		}

		if (spawnnewrock)
		{
			rocks.push_back(new Rock(GameScreenWidth, GameScreenHeight, player, ufo));
			rocks[rockN]->SetModel(rockModels[GetRandomValue(0, 3)].GetModel());
			rocks[rockN]->SetDotModel(dotModel);
			rocks[rockN]->LoadSound(Explode);
			rocks[rockN]->Initialise();

			ufo->rocks.push_back(new RockData());
		}

		switch (size)
		{
			float speed;

		case Rock::Large:
			speed = GetRandomFloat(maxSpeed / 10, maxSpeed / 3);
			rocks[rockN]->Spawn({ GameScreenWidth, GetRandomScreenY(), 0 }, speed, size);
			break;

		case Rock::Medium:
			speed = GetRandomFloat(maxSpeed / 10, maxSpeed / 2);
			rocks[rockN]->Spawn(pos, speed, size);
			break;

		case Rock::Small:
			speed = GetRandomFloat(maxSpeed / 10, maxSpeed);
			rocks[rockN]->Spawn(pos, speed, size);
			break;
		}

		ufo->rocks[rockN]->SetVelocity(rocks[rockN]->Velocity);
	}
}