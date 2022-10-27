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

	Radius = 1.6f;
}

WedgeGroup::~WedgeGroup()
{
}

bool WedgeGroup::Initialise()
{
	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Initialise();
	}

	docked = true;

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

	if (docked)
	{
		float wY = 0.56f; //Off Center on the Y. Needs to be raised a bit.
		float wX = 0.65f;
		float rot = 0.333f;

		Entity::Update(deltaTime);

		wedgePairs[0]->Position.y = Position.y + wY;
		wedgePairs[0]->Position.x = Position.x;
		wedgePairs[1]->Position = { Position.x + wX, Position.y - wY, 0 };
		wedgePairs[1]->RotationZ = (float)PI * rot;
		wedgePairs[2]->Position = { Position.x - wX, Position.y - wY, 0 };
		wedgePairs[2]->RotationZ = ((float)PI * 2) * rot;
	}

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Update(deltaTime);
	}

	CheckScreenEdge();
}

void WedgeGroup::Draw()
{
	Entity::Draw();

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Draw();
	}
}

void WedgeGroup::Undock()
{
	docked = false;
	Velocity = { 0 };
}

void WedgeGroup::Spawn(Vector3 position)
{

}
