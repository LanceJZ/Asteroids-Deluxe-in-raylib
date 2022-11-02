#include "WedgeGroup.h"
#include "raymath.h"

WedgeGroup::WedgeGroup(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	for (int i = 0; i < 3; i++)
	{
		wedgePairs[i] = new WedgePair(windowWidth, windowHeight, player, ufo);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	WedgeGroup::player = player;

	Radius = 1.6f;
}

WedgeGroup::~WedgeGroup()
{
}

bool WedgeGroup::Initialize()
{
	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Initialize();
	}

	wedgepairsDocked = true;
	Enabled = false;

	return false;
}

void WedgeGroup::Load()
{

}

void WedgeGroup::LoadModel(string model)
{
	wedgeModel.LoadModel(model);

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->LoadWedgeModel(wedgeModel.GetModel());
	}
}

void WedgeGroup::Input()
{

}

void WedgeGroup::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	if (wedgepairsDocked)
	{
		if (CheckCollision())
			Collision();

		float wY = 0.75f;
		float wYlower = 0.35f;
		float wX = 0.65f;
		float rot = 0.333f;

		Entity::Update(deltaTime);

		wedgePairs[0]->Position.y = Position.y + wY;
		wedgePairs[0]->Position.x = Position.x;
		wedgePairs[1]->Position = { Position.x + wX, Position.y - wYlower, 0 };
		wedgePairs[1]->RotationZ = (float)PI * rot;
		wedgePairs[2]->Position = { Position.x - wX, Position.y - wYlower, 0 };
		wedgePairs[2]->RotationZ = ((float)PI * 2) * rot;

		CheckScreenEdge();
	}

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Update(deltaTime);
	}
}

void WedgeGroup::Draw()
{
	Entity::Draw();

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Draw();
	}
}

bool WedgeGroup::CheckCollision()
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

void WedgeGroup::Collision()
{
	Undock();
}

void WedgeGroup::Undock()
{
	wedgepairsDocked = false;
	Velocity = { 0 };
	Enabled = false;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->docked = false;
	}
}

void WedgeGroup::Spawn(Vector3 position)
{
	Enabled = true;
	Position = position;


}
