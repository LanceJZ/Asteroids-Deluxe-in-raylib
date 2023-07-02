#include "Shot.h"

Shot::~Shot()
{
}

void Shot::SetManagersRef(Managers& man)
{
	Man = &man;
}

bool Shot::Initialize()
{
	Entity::Initialize();

	Enabled = false;
	Radius = 2.0f;
	Scale = 20;

	return true;
}

bool Shot::BeginRun()
{
	Entity::BeginRun();

	ShotTimerID = Man->EM.AddTimer();

	return true;
}

void Shot::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	CheckScreenEdge();

	if (Man->EM.Timers[ShotTimerID]->Elapsed())
	{
		Man->EM.Timers[ShotTimerID]->Reset();
		Enabled = false;
	}
}

void Shot::Spawn(Vector3 pos, Vector3 vel, float timerAmount)
{
	Position = pos;
	Velocity = vel;
	Enabled = true;

	Man->EM.Timers[ShotTimerID]->Reset(timerAmount);
}