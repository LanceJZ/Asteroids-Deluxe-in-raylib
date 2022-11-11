#include "UFOControl.h"
#include "raymath.h"

UFOControl::UFOControl(float playScreenW, float playScreenH, Player* player)
{
	GameScreenWidth = playScreenW;
	GameScreenHeight = playScreenH;
	UFOControl::player = player;

	ufo = new UFO(playScreenW, playScreenH, player);

	timer = new Timer();
}

bool UFOControl::Initialize()
{
	ufo->Initialise();
	ResetTimer();

	return false;
}

void UFOControl::LoadModel(string ship, vector<Vector3> dotModel)
{
	ufo->LoadModel(ship, dotModel);
}

void UFOControl::LoadSound(Sound exp, Sound big, Sound small, Sound fire)
{
	ufo->LoadSound(exp, big, small, fire);
}

void UFOControl::Update(float deltaTime)
{
	ufo->Update(deltaTime);
	timer->Update(deltaTime);

	if (timer->Elapsed() && !ufo->Enabled)
	{
		SpawnUFO();
	}
	else if (ufo->Enabled)
	{
		ResetTimer();
	}
}

void UFOControl::Draw()
{
	ufo->Draw();
}

void UFOControl::NewGame()
{
	ResetTimer();
	spawnCount = 0;
	ufo->Enabled = false;
	ufo->shot->Enabled = false;
}

void UFOControl::SpawnUFO()
{
	spawnCount++;
	ResetTimer();
	float spawnPercent = (float)(pow(0.915, spawnCount /
		(player->wave + 1)) * 100);

	if (GetRandomFloat(0, 99) < spawnPercent - player->score / 500)
	{
		ufo->size = UFO::Large;
		ufo->Scale = 1;
		ufo->MaxSpeed = 5.0f;
		ufo->Radius = 0.75f;
	}
	else
	{
		ufo->size = UFO::Small;
		ufo->Scale = 0.5f;
		ufo->MaxSpeed = 7.0f;
		ufo->Radius = 0.4f;
	}

	float speed = 0;
	float height = GetRandomFloat(GameScreenHeight / 4, GameScreenHeight / 1.25f);
	float side = 0;

	if (GetRandomFloat(0, 10) < 5)
	{
		speed = 5;
		side = -GameScreenWidth;
	}
	else
	{
		speed = -5;
		side = GameScreenWidth;
	}

	ufo->Spawn({ side, height, 0 }, { speed, 0, 0 });
}

void UFOControl::ResetTimer()
{
	float min = 10 - (player->wave * 0.1f);
	float max = 11 + (player->wave * 0.1f);
	timer->Reset(GetRandomFloat(min, max));
}
