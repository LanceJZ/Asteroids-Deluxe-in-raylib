#pragma once
#include "WedgePair.h"
#include "Player.h"
#include "UFO.h"
#include "raylib.h"

class WedgeGroup : public Entity
{
public:
	bool wedgepairsDocked = true;
	bool newWave = false;

	WedgePair* wedgePairs[3];

	WedgeGroup(float windowWidth, float windowHeight, Player* player, UFO* ufo);
	virtual ~WedgeGroup();
	bool Initialise();
	void Load();
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position);

private:
	LineModel wedgeModel;
	Player* player;

	bool CheckCollision();
	void Collision();
	void Undock();
};

