#pragma once
#include "WedgePair.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"
#include "Entity.h"
#include "Managers.h"

class WedgeGroup : public Entity
{
public:
	WedgePair* WedgePairs[3] = {};

	WedgeGroup();
	virtual ~WedgeGroup();

	void SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo);
	bool Initialize();
	void SetModelID(size_t modelID);
	void Update(float deltaTime);

	void Spawn();
	void NewGame();

private:
	int Score = 50;

	Player* ThePlayer = {};
	UFO* TheUFO = {};
	CrossCom* CC = {};

	bool CheckCollision();
	void Collision();
	void Undock();
	void GoOffScreen();
	void TurnOff();
};

