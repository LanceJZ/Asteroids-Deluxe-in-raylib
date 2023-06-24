#pragma once
#include "raylib.h"
#include "Common.h"
#include "Rock.h"
#include "CrossCom.h"

class RockControl : public Common
{
public:
	bool rockCountUnderFour = false;
	//vector<Rock*> rocks;

	bool Initialize();
	void SetSound(Sound exp);
	void Update(float deltaTime);
	void NewGame(void);
	void NewWave(void);
	void RockHit(Rock* rockHit);

private:
	bool noRocks = false;
	int newRockCount = { 4 };
	Color color = WHITE;

	//LineModel rockModels[4];
	//vector<Vector3> dotModel;
	Sound Explode;

	CrossCom* crossCom;
};

