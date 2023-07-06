#include "Wedge.h"

Wedge::Wedge()
{
}

Wedge::~Wedge()
{
}

void Wedge::SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo)
{
	CC = cc;
	Man = man;
	ThePlayer = player;
	TheUFO = ufo;
}

bool Wedge::Initialize()
{
	LineModel::Initialize();

	Radius = 14.6f;
	Scale = 21.6f;
	Enabled = false;
	ModelColor = { 175, 175, 255, 255 };

	return false;
}

void Wedge::SetModelFromID(size_t modelID)
{
	SetModel(Man->CM.GetLineModel(modelID));
}

void Wedge::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (!Docked)
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

void Wedge::Spawn()
{
	Enabled = true;
	Docked = true;
}

bool Wedge::CheckCollision()
{
	if (CirclesIntersect(*ThePlayer))
	{
		if (!ThePlayer->ShieldHit(Position, Velocity))
		{
			ThePlayer->ScoreUpdate(Score);
			return true;
		}
	}

	for (auto &shot : ThePlayer->Shots)
	{
		if (CirclesIntersect(*shot))
		{
			ThePlayer->ScoreUpdate(Score);
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
	CC->WedgeHit = true;

	TurnOff();
}

void Wedge::ChasePlayer()
{
	RotateVelocity(ThePlayer->Position, TurnSpeed, Speed);
}

void Wedge::ChaseUFO()
{
	RotateVelocity(TheUFO->Position, TurnSpeed, Speed);
}

void Wedge::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity = 0;
	Position = { WindowWidth * 2, 0, 0 };
}

void Wedge::LeavePlay()
{
	PositionedObject::LeavePlay(TurnSpeed, Speed);

	if (OffScreen())
	{
		TurnOff();
	}
}