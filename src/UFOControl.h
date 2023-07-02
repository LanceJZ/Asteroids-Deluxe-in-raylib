#pragma once
#include "raylib.h"
#include "Managers.h"
#include "Common.h"
#include "Player.h"
#include "UFO.h"

class UFOControl : public Common
{
public:

	UFOControl();
	bool Initialize();
	void SetPlayerRef(Player* thePlayer);
	void SetCrossRef(CrossCom& com);
	void SetManagersRef(Managers& man);
	bool BeginRun();
	void Update();

	void NewGame();

	UFO* TheUFO = {};

private:
	int SpawnCount = {0};
	size_t SpawnTimerID = 0;

	CrossCom* CC = {};
	Managers* Man = {};
	Player* ThePlayer = {};

	void SpawnUFO();
	void ResetTimer();
};

