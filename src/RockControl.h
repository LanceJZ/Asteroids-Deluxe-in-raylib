#pragma once
#include <algorithm>
#include "raylib.h"
#include "Common.h"
#include "Rock.h"
#include "CrossCom.h"
#include "EntityManager.h"

class RockControl : public Common
{
public:
	bool Initialize();
	void SetEMRef(EntityManager& em);
	void SetCMRef(ContentManager& cm);
	void SetComRef(CrossCom& com);
	void SetSound(Sound exp);
	void SetRockModels(size_t rockModelRefs[4]);
	void Update(float deltaTime);
	void NewGame(void);
	void NewWave(void);

private:
	bool NoRocks = false;
	int NewRockCount = { 4 };
	size_t RockModelRefs[4];
	std::vector<size_t> RocksIDs;
	std::vector<std::shared_ptr<Rock>> RockRefs;
	Sound Explode;

	CrossCom* Com;
	EntityManager* EM;
	ContentManager* CM;

	void SpawnRocks(Vector3 pos, int count, Rock::RockSize size);
};