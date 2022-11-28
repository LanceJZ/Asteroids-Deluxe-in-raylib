#include "UFO.h"
#include "raymath.h"

UFO::UFO(float windowWidth, float windowHeight, Player* player, CrossCom* crossCom)
{
	UFO::player = player;
	UFO::crossCom = crossCom;
	shot = new Shot(windowWidth, windowHeight);
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
	exploder = new Exploder(dotModel);
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
	fireTimer->Reset(2.75f);
}

void UFO::ResetVectorTimer()
{
	vectorTimer->Reset(3.15f);
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
			Velocity.y = 0;
		}
	}
}

void UFO::FireShot()
{
	float ang = 0;
	float shotSpeed = 15;

	switch (size)
	{
	case UFO::Large:
		if (GetRandomValue(1, 10) < 5)
		{
			ang = GetRandomRadian();
		}
		else
		{
			if (crossCom->wedgeGroupActive)
			{
				ang = AimedShotAtWGroup();
			}
			else
			{
				ang = AimedShot();
			}
		}
		break;
	case UFO::Small:
		ang = AimedShot();
		break;
	}

	if (!shot->Enabled)
	{
		if (!player->gameOver)
		{
			PlaySound(Sound04);
		}

		Vector3 offset = Vector3Add(VelocityFromAngleZ(Radius), Position);
		shot->Spawn(offset,	VelocityFromAngleZ(ang, shotSpeed), 1.75f);
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

	return AngleFromVectorZ(player->Position) +
		GetRandomFloat(-percentChance, percentChance);
}

float UFO::AimedShotAtWGroup()
{
	float percentChance = GetRandomFloat(0.0f, 0.05f);

	return AngleFromVectorZ(crossCom->wedgeGroupPos) +
		GetRandomFloat(-percentChance, percentChance);
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