#pragma once
#include <vector>
#include "raylib.h"
#include "Common.h"
#include "Rock.h"
using namespace std;

class RockControl : public Common
{
public:
	vector<Rock*> rocks;

	RockControl(float screenWidth, float screenHeight, Player* player, UFO* ufo);
	bool Initialize();
	virtual void LoadModel(string modelOne, string modelTwo, string modelThree,	string modelFour);
	void LoadSound(Sound exp);
	virtual void Update(float deltaTime);
	virtual void Draw();
	void NewGame(void);
	void NewWave(void);
	void RockHit(Rock* rockHit);


private:
	int rockCount = { 4 };

	LineModel rockModels[4];
	LineModel dotModel;
	Sound Explode;

	void CreateRocks(void);
	void ClearAllRocks(void);
	void SpawnNewWave(int NumberOfRocks);
	void SpawnRocks(Vector3 pos, int count, Rock::RockSize size);
	void SpawnRock(int rock, float scale, int points, Vector3 position,
		float speed, Rock::RockSize size);
	Player* player;
	UFO* ufo;
};

