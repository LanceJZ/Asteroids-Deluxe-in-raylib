#include "WedgeGroup.h"
#include "raymath.h"

WedgeGroup::WedgeGroup(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom, Color color)
{
	for (int i = 0; i < 3; i++)
	{
		wedgePairs[i] = new WedgePair(windowWidth, windowHeight, player, ufo, crossCom, color);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	WedgeGroup::player = player;
	WedgeGroup::ufo = ufo;
	WedgeGroup::crossCom = crossCom;
	WedgeGroup::color = color;

	Radius = 1.6f;
}

WedgeGroup::~WedgeGroup()
{
	UnloadSound(Sound01);
}

bool WedgeGroup::Initialize()
{
	float rot = 0.333f;
	wedgePairs[0]->Rotation = 0;
	wedgePairs[1]->Rotation = (float)PI * rot;
	wedgePairs[2]->Rotation = ((float)PI * 2) * rot;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Initialize();
	}

	Enabled = false;
	crossCom->newWave = false;
	Position = { 50, 50, 0 };

	return false;
}

void WedgeGroup::LoadSound(Sound explode)
{
	Sound01 = explode;
	SetSoundVolume(Sound01, 0.75f);

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->LoadSound(explode);
	}
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

		crossCom->wedgeGroupPos = Position;

		wedgePairs[0]->Position.y = Position.y + wY;
		wedgePairs[0]->Position.x = Position.x;
		wedgePairs[1]->Position = { Position.x + wX, Position.y - wYlower, 0 };
		wedgePairs[1]->Rotation = (float)PI * rot;
		wedgePairs[2]->Position = { Position.x - wX, Position.y - wYlower, 0 };
		wedgePairs[2]->Rotation = ((float)PI * 2) * rot;

		if (!crossCom->newWave)
		{
			if (Enabled)
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

	crossCom->wedgeGroupActive = true;
	Enabled = true;
	wedgepairsDocked = true;
	Position = position;
	Velocity = velocity;
	float rot = 0.333333f;
	wedgePairs[0]->Rotation = 0;
	wedgePairs[1]->Rotation = (float)PI * rot;
	wedgePairs[2]->Rotation = ((float)PI * 2) * rot;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->Spawn();
	}
}

bool WedgeGroup::CheckCollision()
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

void WedgeGroup::Collision()
{
	if (!player->gameOver)
		PlaySound(Sound01);

	Undock();
}

void WedgeGroup::Undock()
{
	wedgepairsDocked = false;
	Velocity = { 0 };
	Enabled = false;
	crossCom->wedgeGroupActive = false;

	for (auto wedgePair : wedgePairs)
	{
		wedgePair->groupDocked = false;
	}
}