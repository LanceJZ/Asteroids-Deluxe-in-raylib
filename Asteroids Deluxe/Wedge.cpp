#include "Wedge.h"

Wedge::Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	Wedge::player = player;
	Radius = 0.72f;
}

Wedge::~Wedge()
{
}

bool Wedge::Initialize()
{
	docked = true;
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

		ChasePlayer();
	}
}

void Wedge::Draw()
{
	LineModel::Draw();
}

bool Wedge::CheckCollision()
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

void Wedge::Collision()
{
	Enabled = false;
}

void Wedge::ChasePlayer()
{
	RotationVelocity.z = RotateTowardsTargetZ(player->Position, 5.0f);
	Velocity = VelocityFromAngleZ(RotationZ, 5);
}
