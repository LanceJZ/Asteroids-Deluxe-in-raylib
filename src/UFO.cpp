#include "UFO.h"
#include "raymath.h"

UFO::UFO()
{
}

UFO::~UFO()
{
}

bool UFO::Initialize()
{
	LineModel::Initialize();

	Enabled = false;
	ModelColor = { 175, 175, 255, 255 };

	return true;
}

void UFO::SetPlayerRef(Player* thePlayer)
{
	ThePlayer = thePlayer;
}

void UFO::SetCrossRef(CrossCom& com)
{
	CC = &com;
}

void UFO::SetManagerRef(Managers& man)
{
	Man = &man;
	TheShot->SetManagersRef(man);
}

bool UFO::BeginRun()
{
	FireTimerID = Man->EM.AddTimer();
	ChangeVectorTimerID = Man->EM.AddTimer();

	return true;
}

void UFO::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	CheckScreenEdgeY();

	if (CheckReachedSide())
	{
		Enabled = false;
	}

	if (Man->EM.Timers[FireTimerID]->Elapsed())
	{
		FireShot();
	}

	if (Man->EM.Timers[ChangeVectorTimerID]->Elapsed())
	{
		ChangeVector();
	}

	if (CheckCollision())
	{
		Collision();
	}
}

void UFO::Draw()
{
	LineModel::Draw();
}

void UFO::Spawn(int spawnCount)
{
	Enabled = true;
	float fullScale = 20.0f;
	float fullRadius = 17.5f;
	float fullSpeed = 57.0f;

	ResetVectorTimer();
	ResetFireTimer();
	ChangeVector();

	float spawnPercent = (powf(0.915f, (float)spawnCount / (float)(CC->Wave + 1)) * 100);

	if (GetRandomFloat(0, 99) < spawnPercent - ThePlayer->Score / 500)
	{
		TheSize = Large;
		Scale = fullScale;
		MaxSpeed = fullSpeed / 1.3f;
		Radius = fullRadius;
	}
	else
	{
		TheSize = Small;
		Scale = fullRadius / 2;
		MaxSpeed = fullSpeed;
		Radius = fullRadius / 2;
	}

	float speed = 0;
	float height = GetRandomFloat((float)WindowHeight / 4, (float)WindowHeight / 1.25f);
	float side = 0;

	if (GetRandomFloat(0, 10) < 5)
	{
		speed = MaxSpeed;
		side = -WindowWidth;
	}
	else
	{
		speed = -MaxSpeed;
		side = WindowWidth;
	}

	Position = { side, height, 0 };
	Velocity = { speed, 0, 0 };
}

void UFO::Collision()
{
	Enabled = false;
}

void UFO::ResetFireTimer()
{
	float min = 5 - (CC->Wave * 0.1f);
	float max = 5 + min;

	Man->EM.Timers[FireTimerID]->Reset(GetRandomFloat(min, max));
}

void UFO::ResetVectorTimer()
{
	float min = 7 - (CC->Wave * 0.1f);
	float max = 7 + min;

	Man->EM.Timers[ChangeVectorTimerID]->Reset(GetRandomFloat(min, max));
}

void UFO::ChangeVector()
{
	ResetVectorTimer();

	if (GetRandomValue(1, 10) > 2)
	{
		if ((int)Velocity.y == 0)
		{
			if (GetRandomValue(1, 10) < 5)
			{
				Velocity.y = MaxSpeed;
			}
			else
			{
				Velocity.y = -MaxSpeed;
			}
		}
		else
		{
			if (Position.y < WindowHeight - (Radius * 3) &&
				Position.y > -WindowHeight - (Radius * 3))
			{
				Velocity.y = 0;
			}
		}
	}
}

void UFO::FireShot()
{
	ResetFireTimer();

	float angle = 0;
	float shotSpeed = 325;
	bool shootRocks = false;

	switch (TheSize)
	{
	case UFO::Large:
		if (GetRandomValue(1, 10) < 5)
		{
			angle = GetRandomRadian();
		}
		else
		{
			if (CC->WedgeGroupActive)
			{
				angle = AimedShotAtWGroup();
			}
			else
			{
				angle = AimedShot();
			}
		}
		break;
	case UFO::Small:
		if (CC->WedgeGroupActive)
		{
			angle = AimedShotAtWGroup();
		}
		else
		{
			angle = AimedShot();
		}
		break;
	}

	if (!ThePlayer->Enabled && !CC->WedgeGroupActive)
	{
		angle = AimedShotAtRock();
	}

	if (!TheShot->Enabled)
	{
		//if (!player->gameOver)
		//{
		//	PlaySound(Sound04);
		//}

		Vector3 offset = Vector3Add(VelocityFromAngleZ(Radius), Position);
		TheShot->Spawn(offset, VelocityFromAngleZ(angle, shotSpeed), 2.5f);
	}
}

float UFO::AimedShot()
{
	if (!ThePlayer->Enabled)
	{
		return GetRandomRadian();
	}

	float percentChance = 0.2f - (ThePlayer->Score * 0.00001f);

	if (percentChance < 0)
	{
		percentChance = 0;
	}

	float minP = 0.015f - (CC->Wave * 0.0025f);

	if (minP < 0)
		minP = 0;

	float maxP = 0.02f + minP;

	percentChance += GetRandomFloat(minP, maxP);

	return AngleFromVectorZ(ThePlayer->Position) +
		GetRandomFloat(-percentChance, percentChance);
}

float UFO::AimedShotAtWGroup()
{
	return AngleFromVectorZ(CC->WedgeGroupPos);
}

float UFO::AimedShotAtRock()
{
	bool noRocks = true;
	Vector3 closestRockPos = { 0 };
	Vector3 closestRockVel = { 0 };
	float shortestDistance = 200;

	for (int i = 0; i < CC->RockData.size(); i ++)
	{
		if (CC->RockData[i].Enabled)
		{
			noRocks = false;
			float rockDistance = Vector3Distance(Position, CC->RockData[i].Position);

			if (rockDistance < shortestDistance)
			{
				closestRockPos = CC->RockData[i].Position;
				closestRockVel = CC->RockData[i].Velocity;
				shortestDistance = rockDistance;
			}
		}
	}

	if (noRocks)
	{
		return GetRandomRadian();
	}

	Vector3 dist = GetVelocityFromAngleZ(AngleFromVectorZ(closestRockVel), shortestDistance);

	return AngleFromVectorZ(Vector3Add(closestRockPos, Vector3Add(closestRockVel, dist)));
}

void UFO::GiveScore()
{
	switch (TheSize)
	{
	case Large:
		ThePlayer->ScoreUpdate(200);
		break;
	case Small:
		ThePlayer->ScoreUpdate(1000);
		break;
	}
}

bool UFO::CheckCollision()
{
	//if (TheShot->CirclesIntersect(*ThePlayer))
	//{
	//	ThePlayer->ShieldHit(TheShot->Position, TheShot->Velocity);
	//	TheShot->Enabled = false;
	//}

	//if (CirclesIntersect(*ThePlayer))
	//{
	//	if (!ThePlayer->ShieldHit(Position, Velocity))
	//	{
	//		GiveScore();
	//		return true;
	//	}
	//}

	for (auto shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot))
		{
			shot->Enabled = false;
			GiveScore();
			return true;
		}
	}

	return false;
}

bool UFO::CheckReachedSide()
{
	if (X() < -WindowWidth)
	{
		return true;
	}
	if (X() > WindowWidth)
	{
		return true;
	}

	return false;
}