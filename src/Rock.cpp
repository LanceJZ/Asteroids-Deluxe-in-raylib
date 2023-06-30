#include "Rock.h"

Rock::~Rock()
{
}

bool Rock::Initialize()
{
	LineModel::Initialize();

	ModelColor = { 170, 170, 245, 255 };

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
	Rock::Size = size;
	float scale = 30;
	float radius = 58.25f;
	float change = 0;
	Enabled = true;
	BeenHit = false;

	switch (size)
	{
	case Small:
		change = 4.5f;
		Scale = scale / change;
		Radius = radius / change;
		maxVS = 3;
		magnitude = GetRandomFloat(40.1f, 60.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);
		break;
	case Medium:
		change = 1.85f;
		Scale =  scale / change;
		Radius = radius / change;
		maxVS = 2;
		magnitude = GetRandomFloat(30.1f, 50.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);
		break;
	case Large:
		Y(GetRandomFloat(-WindowHeight, WindowHeight));
		Scale = scale;
		Radius = radius;
		maxVS = 1;

		magnitude = GetRandomFloat(20.1f, 40.1f);
		Velocity = GetVelocityFromAngleZ(angle, magnitude);

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
	BeenHit = true;

	//TheExploder.Spawn(Position, 15, Radius);

	if (!ThePlayer->GameOver)
	{
		//PlaySound(Sound01);
	}
}
