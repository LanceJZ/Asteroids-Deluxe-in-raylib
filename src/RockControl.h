#pragma once
#include <algorithm>
#include "Common.h"
#include "Managers.h"
#include "CrossCom.h"
#include "Rock.h"
#include "Player.h"
#include "UFO.h"

class RockControl : public Common
{
public:
	RockControl();
	virtual ~RockControl();

	bool Initialize();
	void SetManagersRef(Managers& man);
	void SetPlayerRef(Player* thePlayer);
	void SetCrossRef(CrossCom& com);
	void SetUFORef(UFO* ufo);
	void SetSoundID(size_t explodeID);
	void SetRockModels(size_t rockModelRefs[4]);

	void Update();

	void NewGame();
	void Debug(bool debugOn);

private:
	int NewRockCount = { 4 };
	size_t RockModelRefs[4];
	size_t ExplodeSoundID = 0;
	std::vector<Rock*> RockRefs = {};

	CrossCom* CC = {};
	Managers* Man = {};
	size_t PlayerID = 0;
	Player* ThePlayer = {};
	UFO* TheUFO = {};

	void SpawnRocks(Vector3 pos, int count, Rock::RockSize size);
	void RockHit();
	void CheckEndOfWave();
	void NewWave();
};