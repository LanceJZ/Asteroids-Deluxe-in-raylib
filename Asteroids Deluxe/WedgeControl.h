#pragma once
#include "WedgeGroup.h"
#include "Player.h"
#include "UFO.h"
#include "Timer.h"
#include "Common.h"
#include "CrossCom.h"

class WedgeControl : public Common
{
public:
	bool ready = false;
	WedgeGroup* wedgeGroup;

	WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo, CrossCom* crosscom);
	virtual ~WedgeControl();

	bool Initialise();
	void LoadSound(Sound explode, Sound spawn);
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Player* player;
	Timer* spawnTimer;
	CrossCom* crossCom;

	Sound spawn;

	void SpawnGroup();
};

