#pragma once
#include "WedgeGroup.h"
#include "Player.h"
#include "UFO.h"
#include "Timer.h"
#include "Common.h"

class WedgeControl : public Common
{
public:
	bool ready = false;
	WedgeGroup* wedgeGroup;

	WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo);
	virtual ~WedgeControl();

	bool Initialise();
	void Load();
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	Player* player;
	Timer* spawnTimer;

	void SpawnGroup();
};

