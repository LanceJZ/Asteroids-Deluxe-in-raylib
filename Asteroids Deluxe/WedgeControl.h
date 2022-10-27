#pragma once
#include "WedgeGroup.h"
#include "Player.h"
#include "UFO.h"
#include "Common.h"
#include "raylib.h"

class WedgeControl : public Common
{
public:
	WedgeGroup* wedgeGroup;

	WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo);
	virtual ~WedgeControl();

	bool Initialise();
	void Load();
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Disperse(); //disperse group.

private:
	Player* player;

	void SpawnGroup();
};

