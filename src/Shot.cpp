#include "Shot.h"

void Shot::SetManagerRef(Managers& man)
{
	Man = &man;
}

bool Shot::Initialize()
{
	Entity::Initialize();

	Enabled = false;
	Radius = 2.0f;
	Scale = 10;

	return true;
}

void Shot::BeginRun()
{
	ShotTimerNumber = Man->EM.AddTimer();
}

void Shot::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	CheckScreenEdge();

	if (Man->EM.Timers[ShotTimerNumber]->Elapsed())
	{
		Enabled = false;
	}
}

void Shot::Spawn(Vector3 pos, Vector3 vel, float timerAmount)
{
	Position = pos;
	Velocity = vel;
	Enabled = true;

	Man->EM.Timers[ShotTimerNumber]->Reset(timerAmount);
}