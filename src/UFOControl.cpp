#include "UFOControl.h"
#include "raymath.h"

UFOControl::UFOControl()
{
}

bool UFOControl::Initialize()
{

	return false;
}

void UFOControl::SetPlayerRef(Player* thePlayer)
{
	ThePlayer = thePlayer;
	TheUFO->SetPlayerRef(thePlayer);
}

void UFOControl::SetCrossRef(CrossCom& com)
{
	CC = &com;
	TheUFO->SetCrossRef(com);
}

void UFOControl::SetManagersRef(Managers& man)
{
	Man = &man;
	TheUFO->SetManagerRef(man);
}

bool UFOControl::BeginRun()
{
	SpawnTimerID = Man->EM.AddTimer();

	return true;
}

void UFOControl::Update()
{
	if (Man->EM.Timers[SpawnTimerID]->Elapsed())
	{
		if (!TheUFO->Enabled) SpawnUFO();
	}
	else if (TheUFO->Enabled)
	{
		ResetTimer();
	}
}

void UFOControl::NewGame()
{
	ResetTimer();
	SpawnCount = 0;
	TheUFO->Enabled = false;
	TheUFO->TheShot->Enabled = false;
}

void UFOControl::SpawnUFO()
{
	ResetTimer();

	if (!ThePlayer->Enabled && !ThePlayer->GameOver) return;

	SpawnCount++;

	TheUFO->Spawn(SpawnCount);
}

void UFOControl::ResetTimer()
{
	float min = 10 - (CC->Wave * 0.1f);
	float max = 10 + min;

	Man->EM.Timers[SpawnTimerID]->Reset(GetRandomFloat(min, max));
}
