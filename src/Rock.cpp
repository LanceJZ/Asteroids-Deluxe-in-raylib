#include "Rock.h"

bool Rock::Initialize()
{
	LineModel::Initialize();

	return true;
}

void Rock::SetReferences(CrossCom& com, std::shared_ptr<Player> thePlayer)
{
	ThePlayer = thePlayer;
	CC = &com;
	//TheUFO = ufo;
}

void Rock::Update(float deltaTime)
{
	LineModel::Update(deltaTime);
	CheckScreenEdge();

	if (CheckCollision())
	{
		Hit();
	}
}

void Rock::Spawn(Vector3 pos, RockSize size)
{
	float magnitude = GetRandomFloat(30.1f, 50.1f);
	float angle = GetRandomRadian();
	float maxVS = 0;

	Position = pos;
	Velocity = GetVelocityFromAngleZ(angle, magnitude);
	Rock::Size = size;
	float scale = 30;
	float radius = 58.25f;
	Enabled = true;
	BeenHit = false;

	switch (size)
	{
	case Small:
		Scale = scale / 3.5f;
		Radius = radius / 3.5f;
		maxVS = 3;
		break;
	case Medium:
		Scale =  scale / 2;
		Radius = radius / 2;
		maxVS = 2;
		break;
	case Large:
		Y(GetRandomFloat(-WindowHeight, WindowHeight));
		Scale = scale;
		Radius = radius;
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

	float rVel = GetRandomFloat(-maxVS, maxVS);

	if (rVel < 0.1)
	{
		rVel++;
	}
	else if (rVel > -0.1)
	{
		rVel--;
	}

	RotationVelocity = rVel;
}

void Rock::SendScoreToPlayer()
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
	for (auto shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot))
		{
			shot->Enabled = false;
			Hit();
			SendScoreToPlayer();

			return true;
		}
	}

	//if (CirclesIntersect(ThePlayer))
	//{
	//	if (!ThePlayer->ShieldHit(Position, Velocity))
	//	{
	//		SendScoreToPlayer();
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

void Rock::Hit()
{
	CC->RockHit = true;
	Enabled = false;

	//TheExploder.Spawn(Position, 15, Radius);

	if (!ThePlayer->GameOver)
	{
		//PlaySound(Sound01);
	}
}
