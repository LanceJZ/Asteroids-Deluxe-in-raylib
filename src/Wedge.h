#pragma once
#include "LineModel.h"
#include "Managers.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"

class Wedge : public LineModel
{
public:
	bool Docked = true;
	bool NewWave = false;

	Wedge();
	virtual ~Wedge();

	void SetRefs(CrossCom* cc, Managers* man, Player* player, UFO* ufo);
	bool Initialize();
	void SetModelFromID(size_t modelID);

	void Update(float deltaTime);

	void Spawn();

private:
	int Score = 200;
	float Speed = 77.89f;
	float TurnSpeed = 0.5f;
	float RotateMagnitude = PI / 2;

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

