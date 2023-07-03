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
	WedgeGroup* TheWedgeGroup = {};

	WedgeControl();
	virtual ~WedgeControl();

	void SetRef(CrossCom* cc, Managers* man, Player* player, UFO* ufo);
	bool Initialise();
	void SetModelID(size_t modelID);

	void Update(float deltaTime);

private:
	size_t SpawnTimerID = 0;

	Player* ThePlayer = {};
	UFO* TheUFO = {};
	CrossCom* CC = {};
	Managers* Man = {};

	void SpawnGroup();
};

