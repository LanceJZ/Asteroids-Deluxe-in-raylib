#include "Rock.h"
#include "raymath.h"

void Rock::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	exploder->Update(deltaTime);
	CheckScreenEdge();

	if (CheckCollision())
	{
		BeenHit = true;
		Enabled = false;

		if (!player->gameOver)
		{
			PlaySound(Sound01);
		}
		//exploder->Spawn(Position, 15, Radius);
	}
}

void Rock::Draw()
{
	Entity::Draw();
	exploder->Draw();
}

bool Rock::Initialise()
{
	exploder = new Exploder();

	return false;
}

void Rock::Spawn(Vector3 pos, float speed, RockSize size)
{
	float magnitude = GetRandomFloat(1.1f, 5.1f);
	float angle = GetRandomRadian();
	Vector3 dir = {cos(angle) * magnitude, sin(angle) * magnitude};

	Position = pos;
	Velocity = dir;
	Rock::size = size;

	switch (size)
	{
	case Small:
		Scale = 0.04666f / 3.5f;
		Radius = 2.10f / 3.5f;
		break;
	case Medium:
		Scale = 0.04666f / 2;
		Radius = 2.10f / 2;
		break;
	case Large:
		Scale = 0.04666f;
		Radius = 2.10f;
		break;
	}

	Enabled = true;
	BeenHit = false;
}

void Rock::LoadModel(Model model)
{
	TheModel = model;
}

void Rock::LoadSound(Sound exp)
{
	Sound01 = exp;
	SetSoundVolume(Sound01, 0.5f);
}

Rock::Rock(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	Rock::player = player;
	Rock::ufo = ufo;
}

void Rock::GiveScore()
{
	switch (size)
	{
	case Large:
		player->ScoreUpdate(20);
		break;
	case Medium:
		player->ScoreUpdate(50);
		break;
	case Small:
		player->ScoreUpdate(100);
		break;
	}
}

bool Rock::CheckCollision()
{
	for (auto shot : player->shots)
	{
		if (CirclesIntersect(shot))
		{
			shot->Enabled = false;
			GiveScore();

			return true;
		}
	}

	if (CirclesIntersect(player))
	{
		player->Hit();
		GiveScore();

		return true;
	}

	if (CirclesIntersect(ufo))
	{
		ufo->Enabled = false;

		return true;
	}

	if (CirclesIntersect(ufo->shot))
	{
		ufo->shot->Enabled = false;

		return true;
	}

	return false;
}
