#pragma once
#include "WedgePair.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"
#include "Entity.h"

class WedgeGroup : public Entity
{
public:
	bool wedgepairsDocked = true;
	bool newWave = false;

	WedgePair* wedgePairs[3];

	WedgeGroup(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom, Color color);
	virtual ~WedgeGroup();
	bool Initialize();
	void LoadSound(Sound explode);
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 position, Vector3 velocity);

private:
	int score = 50;
	Color color = WHITE;

	LineModel wedgeModel;
	Player* player;
	UFO* ufo;
	CrossCom* crossCom;

	bool CheckCollision();
	void Collision();
	void Undock();
};

