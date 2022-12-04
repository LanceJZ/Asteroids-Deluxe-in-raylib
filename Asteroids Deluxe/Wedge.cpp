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
	UnloadSound(Sound01);
}

bool Wedge::Initialize()
{
	TurnOff();

	return false;
}

void Wedge::LoadSound(Sound explode)
{
	Sound01 = explode;
	SetSoundVolume(Sound01, 0.75f);
}

void Wedge::Input()
{

}

void Wedge::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (!docked)
	{
		if (!crossCom->newWave)
		{
			if (player->Enabled)
			{
				ChasePlayer();
			}
			else if (ufo->Enabled)
			{
				ChaseUFO();
			}
			else
			{
				LeavePlay();
			}

			CheckScreenEdge();
		}
		else
		{
			LeavePlay();
		}

		if (CheckCollision())
		{
			Collision();
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

void Wedge::Collision()
{
	if (!player->gameOver)
		PlaySound(Sound01);

	TurnOff();
}

void Wedge::ChasePlayer()
{
	RotateVelocity(player->Position, turnSpeed, speed);
}

void Wedge::ChaseUFO()
{
	RotateVelocity(ufo->Position, turnSpeed, speed);
}

void Wedge::TurnOff()
{
	Enabled = false;
	Velocity = { 0 };
	RotationVelocity.z = 0;
	Position = { 30, 30, 0 };
}

void Wedge::LeavePlay()
{
	PositionedObject::LeavePlay(turnSpeed, speed);

	if (OffScreen())
	{
		Initialize();
	}
}