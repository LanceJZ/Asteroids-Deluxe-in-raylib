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
	void SetPlayerRef(std::shared_ptr<Player> thePlayer);
	void SetCrossRef(CrossCom& com);
	void SetManagersRef(Managers& man);
	bool BeginRun();
	void Update();

	void NewGame();

	std::shared_ptr<UFO> TheUFO;

private:
	int SpawnCount = {0};
	size_t SpawnTimerID = 0;

	CrossCom* CC = {};
	Managers* Man = {};
	std::shared_ptr<Player> ThePlayer;

	void SpawnUFO();
	void ResetTimer();
};

