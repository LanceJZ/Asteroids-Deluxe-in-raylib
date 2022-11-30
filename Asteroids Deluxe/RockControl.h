#pragma once
#include <vector>
#include "raylib.h"
#include "Common.h"
#include "Rock.h"
#include "CrossCom.h"
using namespace std;

class RockControl : public Common
{
public:
	bool rockCountUnderFour = false;
	vector<Rock*> rocks;

	RockControl(float screenWidth, float screenHeight, Player* player, UFO* ufo, CrossCom* crosscom);
	bool Initialize();
	virtual void LoadModel(string modelOne, string modelTwo, string modelThree,
		string modelFour, vector<Vector3> dotModel);
	void LoadSound(Sound exp);
	virtual void Update(float deltaTime);
	virtual void Draw();
	void NewGame(void);
	void NewWave(void);
	void RockHit(Rock* rockHit);


private:
	bool noRocks = false;
	int rockCount = { 4 };

	LineModel rockModels[4];
	vector<Vector3> dotModel;
	Sound Explode;

	//void CreateRocks(void);
	//void ClearAllRocks(void);
	void SpawnRocks(Vector3 pos, int count, Rock::RockSize size);
	//void SpawnRock(int rock, float scale, int points, Vector3 position,
	//	float speed, Rock::RockSize size);
	Player* player;
	UFO* ufo;
	CrossCom* crossCom;
};

