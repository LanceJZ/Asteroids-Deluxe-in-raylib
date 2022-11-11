#include "Rock.h"
#include "raymath.h"

Rock::Rock(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	Rock::player = player;
	Rock::ufo = ufo;
}

void Rock::SetDotModel(vector<Vector3> dotModel)
{
	Rock::dotModel = dotModel;
}

void Rock::LoadSound(Sound exp)
{
	Sound01 = exp;
	SetSoundVolume(Sound01, 0.5f);
}

bool Rock::Initialise()
{
	exploder = new Exploder(dotModel);

	return false;
}

void Rock::Update(float deltaTime)
{
	LineModel::Update(deltaTime);
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

		exploder->Spawn(Position, 15, Radius);
	}
}

void Rock::Draw()
{
	LineModel::Draw();
	exploder->Draw();
}

void Rock::Spawn(Vector3 pos, float speed, RockSize size)
{
	float magnitude = GetRandomFloat(1.1f, 5.1f);
	float angle = GetRandomRadian();
	Vector3 dir = {cos(angle) * magnitude, sin(angle) * magnitude};
	float maxVS = 0;

	Position = pos;
	Velocity = dir;
	Rock::size = size;
	float scale = 1.00666f;

	switch (size)
	{
	case Small:
		Scale = scale / 3.5f;
		Radius = 2.10f / 3.5f;
		maxVS = 3;
		break;
	case Medium:
		Scale =  scale / 2;
		Radius = 2.10f / 2;
		maxVS = 2;
		break;
	case Large:
		Scale = scale;
		Radius = 2.10f;
		maxVS = 1;

		if (Velocity.x > 0)
		{
			X(-WindowWidth);
		}
		else
		{
			X(WindowWidth);
		}

		break;
	}

	float rotVelSpeed = GetRandomFloat(-maxVS, maxVS);
	RotationVelocity = { 0, 0, rotVelSpeed };
	Enabled = true;
	BeenHit = false;
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
		if (player->GetShieldIsOn())
		{
			player->ShieldHit(Position, Velocity);
		}
		else
		{
			//player->Hit();
			GiveScore();
			return true;
		}

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
