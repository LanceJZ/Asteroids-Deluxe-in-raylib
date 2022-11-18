#include "WedgeGroup.h"
#include "raymath.h"

WedgeGroup::WedgeGroup(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom)
{
	for (int i = 0; i < 3; i++)
	{
		wedgePairs[i] = new WedgePair(windowWidth, windowHeight, player, ufo, crossCom);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	WedgeGroup::player = player;
	WedgeGroup::ufo = ufo;
	WedgeGroup::crossCom = crossCom;

	Radius = 1.6f;
}

WedgeGroup::~WedgeGroup()
{
}

bool WedgeGroup::Initialize()
{
	float rot = 0.333f;
	wedgePairs[0]->RotationZ = 0;
	wedgePairs[1]->RotationZ = (float)PI * rot;
	wedgePairs[2]->RotationZ = ((float)PI * 2) * rot;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Initialize();
	}

	Enabled = false;
	crossCom->newWave = false;
	Position = { 30, 30, 0 };

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

void WedgeGroup::Spawn(Vector3 position, Vector3 velocity)
{
	Initialize();

	Enabled = true;
	wedgepairsDocked = true;
	Position = position;
	Velocity = velocity;
	float rot = 0.333333f;
	wedgePairs[0]->RotationZ = 0;
	wedgePairs[1]->RotationZ = (float)PI * rot;
	wedgePairs[2]->RotationZ = ((float)PI * 2) * rot;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Spawn();
	}
}

bool WedgeGroup::CheckCollision()
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