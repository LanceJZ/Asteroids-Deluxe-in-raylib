#pragma once
#include "LineModel.h"
#include "Managers.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"

class Wedge : public LineModel
{
public:
	bool docked = true;
	bool newWave = false;

	Wedge();
	virtual ~Wedge();

	bool Initialize();

	void Update(float deltaTime);
	void Draw();

	void Spawn();

private:
	int score = 200;
	float speed = 3.75f;
	float turnSpeed = 0.5f;
	float rotateMagnitude = PI / 2;

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

