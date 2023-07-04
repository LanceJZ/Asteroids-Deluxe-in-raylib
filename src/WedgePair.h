#pragma once
#include "Wedge.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"
#include "Managers.h"

class WedgePair : public Entity
{
public:
	bool GroupDocked = true;
	bool WedgeDocked = true;
	bool NewWave = false;

	Wedge* Wedges[2] = {};

	WedgePair();
	virtual ~WedgePair();

	void SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo);
	bool Initialize();
	void SetModelID(size_t modelID);
	void Update(float deltaTime);

	void Spawn();

private:
	int Score = 100;
	float Speed = 3.25f;
	float TurnSpeed = 0.25f;

	Player* ThePlayer = {};
	UFO* TheUFO = {};
	CrossCom* CC = {};
	Managers* Man = {};

	bool CheckCollision();
	void Collision();
	void ChasePlayer();
	void ChaseUFO();
	void TurnOff();
	void LeavePlay();
};

