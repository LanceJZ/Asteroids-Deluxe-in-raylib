#include "WedgeGroup.h"
#include "raymath.h"

WedgeGroup::WedgeGroup()
{
}

WedgeGroup::~WedgeGroup()
{
}

void WedgeGroup::SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo)
{
	CC = cc;
	Man = man;
	ThePlayer = player;
	TheUFO = ufo;

	man->EM.AddEntity(this);

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->SetRefs(cc, man, player, ufo);
	}
}

bool WedgeGroup::Initialize()
{
	Entity::Initialize();

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->SetParent(this);
	}

	Enabled = false;
	CC->NewWave = false;
	Position = { WindowWidth * 2, 0, 0 };
	Radius = 1.6f;

	return false;
}

void WedgeGroup::SetModelID(size_t modelID)
{
	for (auto wedgePair : WedgePairs)
	{
		wedgePair->SetModelID(modelID);
	}
}

void WedgeGroup::Update(float deltaTime)
{
	Entity::Update(deltaTime);

}

void WedgeGroup::Spawn()
{
	CC->WedgeGroupActive = true;
	Enabled = true;
	WedgePairsDocked = true;
	Position = { WindowWidth, GetRandomFloat(-WindowHeight, WindowHeight), 0 };
	Velocity = GetRandomVelocity(1.5f);
	float rot = 0.333333f;

	float wY = 0.75f;
	float wYLower = 0.35f;
	float wX = 0.65f;
	float rot = 0.333f;

	WedgePairs[0]->Rotation = 0;
	WedgePairs[1]->Rotation = (float)PI * rot;
	WedgePairs[2]->Rotation = ((float)PI * 2) * rot;
	WedgePairs[0]->Position.y = Position.y + wY;
	WedgePairs[0]->Position.x = Position.x;
	WedgePairs[1]->Position = { Position.x + wX, Position.y - wYLower, 0 };
	WedgePairs[1]->Rotation = (float)PI * rot;
	WedgePairs[2]->Position = { Position.x - wX, Position.y - wYLower, 0 };

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->Spawn();
		ReConnectAsChild(wedgePair);
	}
}

bool WedgeGroup::CheckCollision()
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

void WedgeGroup::Collision()
{
	//if (!ThePlayer->GameOver)
	//	PlaySound(ExplosionSoundID);

	Undock();
}

void WedgeGroup::Undock()
{
	WedgePairsDocked = false;
	Velocity = { 0 };
	Enabled = false;
	CC->WedgeGroupActive = false;

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->GroupDocked = false;
		RemoveChild(wedgePair);
	}

	Position.y = WindowHeight * 2;
}