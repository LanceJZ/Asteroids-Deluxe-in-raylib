#pragma once
#include <algorithm>
#include "Common.h"
#include "Managers.h"
#include "Rock.h"
#include "CrossCom.h"
#include "Player.h"

class RockControl : public Common
{
public:
	RockControl();
	virtual ~RockControl();

	bool Initialize();
	void SetManagerRef(Managers& man);
	void SetReferences(CrossCom& com, std::shared_ptr<Player> thePlayer);
	void SetSoundID(size_t explodeID);
	void SetRockModels(size_t rockModelRefs[4]);

	void Update();

	void NewGame();
	void Debug(bool debugOn);

private:
	int NewRockCount = { 4 };
	size_t RockModelRefs[4];
	size_t ExplodeSoundID = 0;
	std::vector<std::shared_ptr<Rock>> RockRefs;

	CrossCom* CC = {};
	Managers* Man = {};
	size_t PlayerID = 0;
	std::shared_ptr<Player> ThePlayer;

	void SpawnRocks(Vector3 pos, int count, Rock::RockSize size);
	void RockHit();
	void CheckEndOfWave();
	void NewWave();
};