#include "Wedge.h"

Wedge::Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom)
{
	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	Wedge::player = player;
	Wedge::ufo = ufo;
	Wedge::crossCom = crossCom;
	Radius = 0.72f;
}

Wedge::~Wedge()
{
	UnloadSound(Sound01);
}

bool Wedge::Initialize()
{
	TurnOff();

	return false;
}

void Wedge::LoadSound(Sound explode)
{
	Sound01 = explode;
	SetSoundVolume(Sound01, 0.75f);
}

void Wedge::Input()
{

}

void Wedge::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (!docked)
	{
		if (CheckCollision())
		{
			Collision();
		}

		if (player->Enabled && !crossCom->newWave)
		{
			ChasePlayer();
		}
		else if (ufo->Enabled && !crossCom->newWave)
		{
			ChaseUFO();
		}
		else
		{
			RotationVelocity.z = 0;
			Velocity = VelocityFromAngleZ(RotationZ, 5);
		}

		if (!crossCom->newWave)
		{
			CheckScreenEdge();
		}
		else
		{
			if (OffScreen())
			{
				Initialize();
			}
		}
	}
}

void Wedge::Draw()
{
	LineModel::Draw();
}

void Wedge::Spawn()
{
	Enabled = true;
	docked = true;
}

bool Wedge::CheckCollision()
{
	if (CirclesIntersect(player))
	{
		if (!player->ShieldHit(Position, Velocity))
		{
			player->ScoreUpdate(score);
			return true;
		}
	}

	for (auto shot : player->shots)
	{
		if (CirclesIntersect(shot))
		{
			player->ScoreUpdate(score);
			shot->Enabled = false;
			return true;
		}
	}

	if (CirclesIntersect(ufo))
	{
		ufo->Collision();
		return true;
	}

	if (CirclesIntersect(ufo->shot))
	{
		ufo->shot->Enabled = false;
		return true;
	}

	return false;
}

void Wedge::Collision()
{
	if (!player->gameOver)
		PlaySound(Sound01);

	TurnOff();
}

void Wedge::ChasePlayer()
{
	RotationVelocity.z = PositionedObject::RotateTowardsTargetZ(player->Position, turnSpeed);
	Velocity = VelocityFromAngleZ(RotationZ, speed);
}

void Wedge::ChaseUFO()
{
	RotationVelocity.z = RotateTowardsTargetZ(ufo->Position, turnSpeed);
	Velocity = VelocityFromAngleZ(RotationZ, speed);
}

void Wedge::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity.z = 0;
	Position = { 30, 30, 0 };
}
