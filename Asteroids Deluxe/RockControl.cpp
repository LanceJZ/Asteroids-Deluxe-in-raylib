#include "RockControl.h"
#include <vector>

void RockControl::NewGame(void)
{
	for (auto rock : rocks)
	{
		rock->Enabled = false;
	}

	rockCount = 4;
	NewWave();
}

void RockControl::NewWave(void)
{
	player->wave++;
	SpawnNewWave(rockCount);

	if (rockCount < 12 && !player->gameOver) //TODO: Check at home, let run while in Game Over with this checked.
		rockCount++;
}


void RockControl::LoadModel(string modelOne, string modelTwo, string modelThree, string modelFour)
{
	rockModels[0] = modelOne;
	rockModels[1] = modelTwo;
	rockModels[2] = modelThree;
	rockModels[3] = modelFour;
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

	if (rockHit)
	{
		RockHit(rockWasHit);
	}
}

void RockControl::Draw(void)
{
	for (auto rock : rocks)
	{
		rock->Draw();
	}
}

bool RockControl::Initialise()
{

	return false;
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
		bool spawnWave = true;

		for (auto rock: rocks)
		{
			if (rock->Enabled)
				spawnWave = false;
		}

		if (spawnWave)
			NewWave();
		break;
	}
}

RockControl::RockControl(float screenWidth, float screenHeight, Player* player, UFO* ufo)
{
	GameScreenWidth = screenWidth;
	GameScreenHeight = screenHeight;
	RockControl::player = player;
	RockControl::ufo = ufo;
}

void RockControl::SpawnNewWave(int numberOfRocks)
{
	SpawnRocks({ 0, 0, 0 }, numberOfRocks, Rock::Large);
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
			rocks[rockN]->LoadModel(rockModels[GetRandomValue(0, 3)]);
			rocks[rockN]->LoadSound(Explode);
			rocks[rockN]->Initialise();
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
	}
}