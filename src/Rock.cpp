#include "Rock.h"

bool Rock::Initialize()
{
	LineModel::Initialize();

	return true;
}

void Rock::SetReferences(std::shared_ptr<Player> thePlayer)
{
	ThePlayer = thePlayer;
	//TheUFO = ufo;
}

void Rock::Update(float deltaTime)
{
	LineModel::Update(deltaTime);
	CheckScreenEdge();

	if (CheckCollision())
	{
		BeenHit = true;
		Enabled = false;

		if (!ThePlayer->GameOver)
		{
			//PlaySound(Sound01);
		}

		//TheExploder.Spawn(Position, 15, Radius);
	}
}

void Rock::Spawn(Vector3 pos, float speed, RockSize size)
{
	float magnitude = GetRandomFloat(1.1f, 5.1f);
	float angle = GetRandomRadian();
	Vector3 dir = {cos(angle) * magnitude, sin(angle) * magnitude};
	float maxVS = 0;

	Position = pos;
	Velocity = dir;
	Rock::Size = size;
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
	RotationVelocity = rotVelSpeed;
	Enabled = true;
	BeenHit = false;
}

void Rock::GiveScore()
{
	switch (Size)
	{
	case Large:
		ThePlayer->ScoreUpdate(20);
		break;
	case Medium:
		ThePlayer->ScoreUpdate(50);
		break;
	case Small:
		ThePlayer->ScoreUpdate(100);
		break;
	}
}

bool Rock::CheckCollision()
{
	//for (auto &shot : ThePlayer->Shots)
	//{
	//	if (CirclesIntersect(&shot))
	//	{
	//		shot.Enabled = false;
	//		GiveScore();

	//		return true;
	//	}
	//}

	//if (CirclesIntersect(ThePlayer))
	//{
	//	if (!ThePlayer->ShieldHit(Position, Velocity))
	//	{
	//		GiveScore();
	//		return true;
	//	}
	//}

	//if (CirclesIntersect(TheUFO))
	//{
	//	TheUFO->Enabled = false;

	//	return true;
	//}

	//if (CirclesIntersect(&TheUFO->TheShot))
	//{
	//	TheUFO->TheShot.Enabled = false;

	//	return true;
	//}

	return false;
}
