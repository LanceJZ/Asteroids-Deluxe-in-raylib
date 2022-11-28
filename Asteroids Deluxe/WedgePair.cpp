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

	if (wedgeDocked)
	{
		Vector3 pos = VelocityFromAngleZ(RotationZ, 0.65f);

		wedges[1]->X(Position.x - pos.x);
		wedges[1]->Y(Position.y - pos.y);
		wedges[0]->X(pos.x + Position.x);
		wedges[0]->Y(pos.y + Position.y);
		wedges[1]->RotationZ = (float)PI + RotationZ;
		wedges[0]->RotationZ = RotationZ;
	}

	if (!docked && wedgeDocked)
	{
		if (player->Enabled && !crossCom->newWave)
		{
			ChasePlayer();
		}
		else
		{
			RotationVelocity.z = 0;
			Velocity = VelocityFromAngleZ(RotationZ, 5);
		}

		if (CheckCollision())
		{
			Collision();
		}
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

	for (auto wedge : wedges)
	{
		wedge->Update(deltaTime);
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
	docked = true;
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
		player->Hit();
		return true;
	}

	for (auto shot : player->shots)
	{
		if (CirclesIntersect(shot))
		{
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
	PlaySound(Sound01);

	wedgeDocked = false;
	TurnOff();

	for (auto wedge : wedges)
	{
		wedge->docked = false;
	}
}

void WedgePair::ChasePlayer()
{
	RotationVelocity.z = RotateTowardsTargetZ(player->Position, 5.0f);
	Velocity = VelocityFromAngleZ(RotationZ, 5);
}

void WedgePair::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity.z = 0;
	Position = { 30, 30, 0 };
}
