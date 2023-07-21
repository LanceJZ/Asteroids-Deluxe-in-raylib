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
	ThePlayer = player;
	TheUFO = ufo;

	for (int i = 0; i < 3; i++)
	{
		WedgePairs[i] = new WedgePair();
		man->EM.AddEntity(WedgePairs[i]);
		WedgePairs[i]->SetRefs(cc, man, player, ufo);
	}

	CC->NewWave = false;
}

bool WedgeGroup::Initialize()
{
	Entity::Initialize();

	Enabled = false;
	Position = { WindowWidth * 2, 0, 0 };
	Radius = 33.0f;

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

	float wY = 15.57692f;//20.76923 times the old one.
	float wYLower = 7.26923f;//20.76923 times the old one.
	float wX = 13.49999f;//20.76923 times the old one.

	WedgePairs[0]->Position.y = Position.y + wY;
	WedgePairs[0]->Position.x = Position.x;
	WedgePairs[1]->Position = { Position.x + wX, Position.y - wYLower, 0 };
	WedgePairs[2]->Position = { Position.x - wX, Position.y - wYLower, 0 };

	if (CC->NewWave)
	{
		GoOffScreen();
	}
	else
	{
		CheckScreenEdge();
	}

	if (CheckCollision()) Collision();
}

void WedgeGroup::Spawn()
{
	CC->WedgeGroupActive = true;
	CC->NewWave = false;
	Enabled = true;
	Position = { WindowWidth, GetRandomFloat(-WindowHeight, WindowHeight), 0 };
	Velocity = GetRandomVelocity(45.5f);

	Velocity.x = PI / 2 * 22.75f;
	Velocity.y = PI / 2 * 22.75f;

	float rot = 0.333333f;
	float wY = 15.57692f;//20.76923 times the old one.
	float wYLower = 7.26923f;//20.76923 times the old one.
	float wX = 13.49999f;//20.76923 times the old one.

	WedgePairs[0]->Rotation = 0;
	WedgePairs[1]->Rotation = (float)PI * rot;
	WedgePairs[2]->Rotation = ((float)PI * 2) * rot;
	//WedgePairs[0]->Position.y = Position.y + wY;
	//WedgePairs[0]->Position.x = Position.x;
	//WedgePairs[1]->Position = { Position.x + wX, Position.y - wYLower, 0 };
	//WedgePairs[2]->Position = { Position.x - wX, Position.y - wYLower, 0 };

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->Spawn();
		//ReConnectAsChild(wedgePair);
	}
}

void WedgeGroup::NewGame()
{
	TurnOff();
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

	for (auto shot : ThePlayer->Shots)
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
	Velocity = { 0 };
	Enabled = false;
	CC->WedgeGroupActive = false;

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->GroupDocked = false;
		//RemoveChild(wedgePair);
	}

	Position.x = WindowWidth * 2;
}

void WedgeGroup::GoOffScreen()
{
	if (OffScreen())
	{
		TurnOff();
	}
}

void WedgeGroup::TurnOff()
{
	Enabled = false;

	for (auto wedgePair : WedgePairs)
	{
		wedgePair->Enabled = false;

		for (auto wedge : wedgePair->Wedges)
		{
			wedge->Enabled = false;
		}
	}
}
