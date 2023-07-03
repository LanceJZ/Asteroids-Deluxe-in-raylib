#include "WedgePair.h"

WedgePair::WedgePair()
{
}

WedgePair::~WedgePair()
{
}

void WedgePair::SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo)
{
	CC = cc;
	Man = man;
	ThePlayer = player;
	TheUFO = ufo;

	man->EM.AddEntity(this);

	for (auto wedge : Wedges)
	{
		wedge->SetRefs(cc, man, player, ufo);
	}
}

bool WedgePair::Initialize()
{
	Radius = 0.95f;
	TurnOff();

	return false;
}

void WedgePair::SetModelID(size_t modelID)
{
	for (auto wedge : Wedges)
	{
		wedge->SetModelFromID(modelID);
	}
}

void WedgePair::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	for (auto wedge : Wedges)
	{
		wedge->Update(deltaTime);
	}

	if (WedgeDocked) //Still together in a pair.
	{
		Vector3 pos = VelocityFromAngleZ(Rotation, 0.65f);

		Wedges[0]->X(pos.x + Position.x);
		Wedges[1]->X(Position.x - pos.x);
		Wedges[0]->Y(pos.y + Position.y);
		Wedges[1]->Y(Position.y - pos.y);
		Wedges[0]->Rotation = Rotation;
		Wedges[1]->Rotation = (float)PI + Rotation;

		if (!GroupDocked) //Not in the group.
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
}

void WedgePair::Draw()
{
	Entity::Draw();
}

void WedgePair::Spawn()
{
	Enabled = true;
	WedgeDocked = true;
	GroupDocked = true;
	Wedges[0]->Rotation = Rotation;
	Wedges[1]->Rotation = (float)PI + Rotation;

	for (auto wedge : Wedges)
	{
		wedge->Spawn();
	}
}

bool WedgePair::CheckCollision()
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

void WedgePair::Collision()
{
	//if (!ThePlayer->GameOver)
	//	PlaySound(ExplodeSoundID);

	WedgeDocked = false;
	TurnOff();

	for (auto wedge : Wedges)
	{
		wedge->Docked = false;
	}
}

void WedgePair::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity = 0;
	Position = { 30, 30, 0 };
}

void WedgePair::ChasePlayer()
{
	RotateVelocity(ThePlayer->Position, TurnSpeed, Speed);
}

void WedgePair::ChaseUFO()
{
	RotateVelocity(TheUFO->Position, TurnSpeed, Speed);
}

void WedgePair::LeavePlay()
{
	PositionedObject::LeavePlay(TurnSpeed, Speed);

	if (OffScreen())
	{
		Initialize();
	}
}