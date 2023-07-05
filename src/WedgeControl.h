#pragma once
#include "WedgeGroup.h"
#include "Player.h"
#include "UFO.h"
#include "Common.h"
#include "CrossCom.h"
#include "Managers.h"

class WedgeControl : public Common
{
public:
	bool ready = false;
	WedgeGroup* WG = {};

	WedgeControl();
	virtual ~WedgeControl();

	void SetRef(CrossCom* cc, Managers* man, Player* player, UFO* ufo);
	bool Initialize();
	void SetModelID(size_t modelID);

	void Update();

	void SpawnGroup();

private:
	size_t SpawnTimerID = 0;

	Player* ThePlayer = {};
	UFO* TheUFO = {};
	CrossCom* CC = {};
	Managers* Man = {};

};

