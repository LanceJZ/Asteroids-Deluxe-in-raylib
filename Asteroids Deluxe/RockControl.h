#pragma once
#include <vector>
#include "raylib.h"
#include "Common.h"
#include "Rock.h"
using namespace std;

class RockControl : public Common
{
public:
	void NewGame(void);
	void NewWave(void);
	vector<Rock*> rocks;

	virtual void LoadModel(string modelOne, string modelTwo, string modelThree,	string modelFour);
	void LoadSound(Sound exp);
	virtual void Update(float deltaTime);
	virtual void Draw();
	bool Initialize();

	void RockHit(Rock* rockHit);

	RockControl(float screenWidth, float screenHeight, Player* player, UFO* ufo);


private:
	int rockCount = { 4 };

	string rockModels[4];
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

