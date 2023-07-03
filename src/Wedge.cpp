#include "Wedge.h"

Wedge::Wedge()
{
}

Wedge::~Wedge()
{
}

bool Wedge::Initialize()
{
	TurnOff();

	return false;
}

void Wedge::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (!docked)
	{
		if (!CC->NewWave)
		{
			if (ThePlayer->Enabled)
			{
				ChasePlayer();
			}
			else if (TheUFO->Enabled)
			{
				ChaseUFO();
			}
			else
			{
				LeavePlay();
			}

			CheckScreenEdge();
		}
		else
		{
			LeavePlay();
		}

		if (CheckCollision())
		{
			Collision();
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
	if (CirclesIntersect(*ThePlayer))
	{
		if (!ThePlayer->ShieldHit(Position, Velocity))
		{
			ThePlayer->ScoreUpdate(score);
			return true;
		}
	}

	for (auto &shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot))
		{
			ThePlayer->ScoreUpdate(score);
			shot->Enabled = false;
			return true;
		}
	}

	if (CirclesIntersect(*TheUFO))
	{
		TheUFO->Collision();
		return true;
	}

	if (CirclesIntersect(*TheUFO->TheShot))
	{
		TheUFO->TheShot->Enabled = false;
		return true;
	}

	return false;
}

void Wedge::Collision()
{
	//if (!ThePlayer->GameOver)
	//	PlaySound(ExplodeSoundID);

	TurnOff();
}

void Wedge::ChasePlayer()
{
	RotateVelocity(ThePlayer->Position, turnSpeed, speed);
}

void Wedge::ChaseUFO()
{
	RotateVelocity(TheUFO->Position, turnSpeed, speed);
}

void Wedge::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity = 0;
	Position = { 30, 30, 0 };
}

void Wedge::LeavePlay()
{
	PositionedObject::LeavePlay(turnSpeed, speed);

	if (OffScreen())
	{
		Initialize();
	}
}