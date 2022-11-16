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
}

bool Wedge::Initialize()
{
	Enabled = false;

	return false;
}

void Wedge::Load()
{

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
			ChasePlayer();

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

void Wedge::Collision()
{
	Enabled = false;
	RotationVelocity.z = 0;
	Velocity = { 0 };
	Position = { 30, 30, 0 };
}

void Wedge::ChasePlayer()
{
	RotationVelocity.z = PositionedObject::RotateTowardsTargetZ(player->Position, 5.0f);
	Velocity = VelocityFromAngleZ(RotationZ, 5);
}
