#include "WedgePair.h"

WedgePair::WedgePair(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom)
{
	for (int i = 0; i < 2; i++)
	{
		wedges[i] = new Wedge(windowWidth, windowHeight, player, ufo, crossCom);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	WedgePair::player = player;
	WedgePair::ufo = ufo;
	WedgePair::crossCom = crossCom;

	Radius = 0.95f;
}

WedgePair::~WedgePair()
{
	UnloadSound(Sound01);
}

void WedgePair::LoadWedgeModel(vector<Vector3> model)
{
	wedgeModel.SetModel(model);
	SetSoundVolume(Sound01, 0.75f);

	for (auto wedge : wedges)
	{
		wedge->SetModel(wedgeModel.GetModel());
	}
}

bool WedgePair::Initialize()
{
	wedges[0]->RotationZ = RotationZ;
	wedges[1]->RotationZ = (float)PI + RotationZ;

	for (auto wedge : wedges)
	{
		wedge->Initialize();
	}

	TurnOff();

	return false;
}

void WedgePair::LoadSound(Sound explode)
{
	Sound01 = explode;

	for (auto wedge : wedges)
	{
		wedge->LoadSound(explode);
	}
}

void WedgePair::LoadModel(string model)
{
}

void WedgePair::Input()
{

}

void WedgePair::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	for (auto wedge : wedges)
	{
		wedge->Update(deltaTime);
	}

	if (wedgeDocked) //Still together in a pair.
	{
		Vector3 pos = VelocityFromAngleZ(RotationZ, 0.65f);

		wedges[1]->X(Position.x - pos.x);
		wedges[1]->Y(Position.y - pos.y);
		wedges[0]->X(pos.x + Position.x);
		wedges[0]->Y(pos.y + Position.y);
		wedges[1]->RotationZ = (float)PI + RotationZ;
		wedges[0]->RotationZ = RotationZ;

		if (!groupDocked) //Not in the group.
		{
			if (!crossCom->newWave)
			{
				if (player->Enabled)
				{
					ChasePlayer();
				}
				else if (ufo->Enabled)
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

	for (auto wedge : wedges)
	{
		wedge->Draw();
	}
}

void WedgePair::Spawn()
{
	Enabled = true;
	wedgeDocked = true;
	groupDocked = true;
	wedges[0]->RotationZ = RotationZ;
	wedges[1]->RotationZ = (float)PI + RotationZ;

	for (auto wedge : wedges)
	{
		wedge->Spawn();
	}
}

bool WedgePair::CheckCollision()
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

void WedgePair::Collision()
{
	if (!player->gameOver)
		PlaySound(Sound01);

	wedgeDocked = false;
	TurnOff();

	for (auto wedge : wedges)
	{
		wedge->docked = false;
	}
}

void WedgePair::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity.z = 0;
	Position = { 30, 30, 0 };
}

void WedgePair::ChasePlayer()
{
	RotateVelocity(player->Position, turnSpeed, speed);
}

void WedgePair::ChaseUFO()
{
	RotateVelocity(ufo->Position, turnSpeed, speed);
}

void WedgePair::LeavePlay()
{
	PositionedObject::LeavePlay(turnSpeed, speed);

	if (OffScreen())
	{
		Initialize();
	}
}