#pragma once
#include "LineModel.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"

class Wedge : public LineModel
{
public:
	bool docked = true;
	bool newWave = false;

	Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom);
	virtual ~Wedge();

	bool Initialize();
	void LoadSound(Sound explode);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn();

private:
	int score = 200;
	float speed = 3.75f;
	float turnSpeed = 0.75f;
	float rotateMagnitude = PI / 2;

	Player* player;
	UFO* ufo;
	CrossCom* crossCom;

	bool CheckCollision();
	void Collision();
	void ChasePlayer();
	void ChaseUFO();
	void TurnOff();
};

