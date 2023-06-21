#include "UFO.h"
#include "raymath.h"

UFO::UFO(float windowWidth, float windowHeight, Player* player, CrossCom* crossCom, Color color)
{
	UFO::player = player;
	UFO::crossCom = crossCom;
	UFO::color = color;
	LineModel::ModelColor = color;
	shot = new Shot(windowWidth, windowHeight);
	shot->ModelColor = color;
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	fireTimer = new Timer();
	vectorTimer = new Timer();
}

UFO::~UFO()
{
	UnloadSound(Sound01);
	UnloadSound(Sound02);
	UnloadSound(Sound03);
	UnloadSound(Sound04);
}

void UFO::LoadModel(string ship, vector<Vector3> dotModel)
{
	LineModel::LoadModel(ship);
	shot->SetModel(dotModel);
	exploder = new Exploder(dotModel, color);
}

void UFO::LoadSound(Sound exp, Sound big, Sound small, Sound fire)
{
	Sound01 = exp;
	Sound02 = big;
	Sound03 = small;
	Sound04 = fire;

	SetSoundVolume(Sound01, 0.5f);
	SetSoundVolume(Sound02, 0.5f);
	SetSoundVolume(Sound03, 0.5f);
	SetSoundVolume(Sound04, 0.5f);
}

bool UFO::Initialise()
{
	Enabled = false;

	return false;
}

void UFO::Update(float deltaTime)
{
	LineModel::Update(deltaTime);
	exploder->Update(deltaTime);
	shot->Update(deltaTime);

	if (Enabled)
	{
		fireTimer->Update(deltaTime);
		vectorTimer->Update(deltaTime);
		CheckScreenEdgeY();

		if (CheckReachedSide())
		{
			Enabled = false;
		}

		if (vectorTimer->Elapsed())
		{
			ChangeVector();
			ResetVectorTimer();
		}

		if (fireTimer->Elapsed())
		{
			FireShot();
			ResetFireTimer();
		}

		if (!player->gameOver)
		{
			switch (size)
			{
			case UFO::Small:
				if (!IsSoundPlaying(Sound03))
				{
					PlaySound(Sound03);
				}
				break;
			case UFO::Large:
				if (!IsSoundPlaying(Sound02))
				{
					PlaySound(Sound02);
				}
				break;
			default:
				break;
			}
		}
	}

	if (CheckCollision())
	{
		Collision();
	}
}

void UFO::Draw()
{
	LineModel::Draw();
	exploder->Draw();
	shot->Draw();
}

void UFO::Spawn(Vector3 pos, Vector3 vel)
{
	Position = pos;
	Velocity = vel;
	Enabled = true;

	ResetVectorTimer();
	ResetFireTimer();
	ChangeVector();
}

void UFO::Collision()
{
	Enabled = false;
	exploder->Spawn(Position, 15, radius / 2.0f);

	if (!player->gameOver)
	{
		PlaySound(Sound01);
		StopSound(Sound02);
		StopSound(Sound03);
	}
}

void UFO::ResetFireTimer()
{
	fireTimer->Reset(GetRandomFloat(0.75f, 2.75f));
}

void UFO::ResetVectorTimer()
{
	vectorTimer->Reset(GetRandomFloat(1.25f, 3.15f));
}

void UFO::ChangeVector()
{
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
			if (Position.y < WindowHeight - (radius * 3) && Position.y > -WindowHeight - (radius * 3))
			{
				Velocity.y = 0;
			}
		}
	}
}

void UFO::FireShot()
{
	float angle = 0;
	float shotSpeed = 15;
	bool shootRocks = false;

	switch (size)
	{
	case UFO::Large:
		if (GetRandomValue(1, 10) < 5)
		{
			angle = GetRandomRadian();
		}
		else
		{
			if (crossCom->wedgeGroupActive)
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
		if (crossCom->wedgeGroupActive)
		{
			angle = AimedShotAtWGroup();
		}
		else
		{
			angle = AimedShot();
		}
		break;
	}

	if (!player->Enabled && !crossCom->wedgeGroupActive)
	{
		angle = AimedShotAtRock();
	}

	if (!shot->Enabled)
	{
		if (!player->gameOver)
		{
			PlaySound(Sound04);
		}

		Vector3 offset = Vector3Add(VelocityFromAngleZ(Radius), Position);
		shot->Spawn(offset,	VelocityFromAngleZ(angle, shotSpeed), 2.5f);
	}
}

float UFO::AimedShot()
{
	if (!player->Enabled)
	{
		return GetRandomRadian();
	}

	float percentChance = 0.2f - (player->score * 0.00001f);

	if (percentChance < 0)
	{
		percentChance = 0;
	}

	percentChance += GetRandomFloat(0.0f, 0.05f);

	return AngleFromVectorZ(player->Position) + GetRandomFloat(-percentChance, percentChance);
}

float UFO::AimedShotAtWGroup()
{
	float percentChance = GetRandomFloat(0.0f, 0.05f);

	return AngleFromVectorZ(crossCom->wedgeGroupPos) + GetRandomFloat(-percentChance, percentChance);
}

float UFO::AimedShotAtRock()
{
	bool noRocks = true;
	Vector3 closestRockPos = { 0 };
	Vector3 closestRockVel = { 0 };
	float shortistDistance = 200;

	for (auto rock : rocks)
	{
		if (rock->Enabled)
		{
			noRocks = false;

			float rockDistance = Vector3Distance(Position, rock->Position);

			if (rockDistance < shortistDistance)
			{
				closestRockPos = rock->Position;
				closestRockVel = rock->Velocity;
				shortistDistance = rockDistance;
			}
		}
	}

	if (noRocks)
	{
		return GetRandomRadian();
	}

	//float spawnPercent = (float)(pow(0.915, spawnCount / (player->wave + 1)) * 100);

	float aimCurrection = AngleFromVectorZ(closestRockVel) * 0.002f;

	float adjustedCurrection = powf(aimCurrection, shortistDistance * 0.00175f);

	//if ((closestRockVel.y > 0 && closestRockPos.y < Y()) || (closestRockVel.x > 0 && closestRockPos.x < X()) ||
	//	(closestRockVel.x > 0 && closestRockPos.y < Y()) || (closestRockVel.y > 0 && closestRockPos.x < X()))
	//{
	//	adjustedCurrection *= -1;
	//}

	//if (closestRockVel.y > 0 && closestRockPos.y > Y())
	//{
	//	adjustedCurrection *= -1;
	//}

	return AngleFromVectorZ(closestRockPos) + aimCurrection;
}

void UFO::GiveScore()
{
	switch (size)
	{
	case Large:
		player->ScoreUpdate(200);
		break;
	case Small:
		player->ScoreUpdate(1000);
		break;
	}
}

bool UFO::CheckCollision()
{
	if (shot->CirclesIntersect(player))
	{
		player->ShieldHit(shot->Position, shot->Velocity);
		shot->Enabled = false;
	}

	if (CirclesIntersect(player))
	{
		if (!player->ShieldHit(Position, Velocity))
		{
			GiveScore();
			return true;
		}
	}

	for (auto shot : player->shots)
	{
		if (CirclesIntersect(shot))
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