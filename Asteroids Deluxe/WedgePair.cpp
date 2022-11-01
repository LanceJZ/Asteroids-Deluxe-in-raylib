#include "WedgePair.h"

WedgePair::WedgePair(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	for (int i = 0; i < 2; i++)
	{
		wedges[i] = new Wedge(windowWidth, windowHeight, player, ufo);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	WedgePair::player = player;

	Radius = 0.6f;
}

WedgePair::~WedgePair()
{
}

void WedgePair::LoadWedgeModel(vector<Vector3> model)
{
	wedgeModel.SetModel(model);

	for (auto wedge : wedges)
	{
		wedge->SetModel(wedgeModel.GetModel());
	}
}

bool WedgePair::Initialize()
{
	for (auto wedge : wedges)
	{
		wedge->Initialize();
	}

	wedgeDocked = true;

	return false;
}

void WedgePair::Load()
{

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

		wedges[1]->RotationZ = (float)PI + RotationZ;
		wedges[1]->X(Position.x - pos.x);
		wedges[1]->Y(Position.y - pos.y);
		wedges[0]->RotationZ = RotationZ;
		wedges[0]->X(pos.x + Position.x);
		wedges[0]->Y(pos.y + Position.y);
	}

	if (!docked && wedgeDocked)
	{
		ChasePlayer();

		if (CheckCollision())
		{
			Collision();
		}
	}

	for (auto wedge : wedges)
	{
		wedge->Update(deltaTime);
	}
}

void WedgePair::Draw()
{
	for (auto wedge : wedges)
	{
		wedge->Draw();
	}
}

bool WedgePair::CheckCollision()
{
	if (CirclesIntersect(player))
	{

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

	return false;
}

void WedgePair::Collision()
{
	wedgeDocked = false;
	Velocity = { 0 };
	Enabled = false;

	for (auto wedge : wedges)
	{
		wedge->docked = false;
	}
}

void WedgePair::ChasePlayer()
{
	RotationVelocity.z = RotateTwordsTargetZ(player->Position, 5.0f);
	Velocity = VelocityFromAngleZ(RotationZ, 5);
}