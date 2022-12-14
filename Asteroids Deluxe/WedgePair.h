#pragma once
#include "Wedge.h"
#include "Player.h"
#include "UFO.h"
#include "CrossCom.h"

class WedgePair : public Entity
{
public:
	bool groupDocked = true;
	bool wedgeDocked = true;
	bool newWave = false;

	Wedge* wedges[2];

	WedgePair(float windowWidth, float windowHeight, Player* player, UFO* ufo, CrossCom* crossCom, Color color);
	virtual ~WedgePair();

	bool Initialize();
	void LoadSound(Sound explode);
	void LoadModel(string model);
	void LoadWedgeModel(vector<Vector3> model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn();

private:
	int score = 100;
	float speed = 3.25f;
	float turnSpeed = 0.25f;
	Color color = WHITE;

	LineModel wedgeModel;
	Player* player;
	UFO* ufo;
	CrossCom* crossCom;

	bool CheckCollision();
	void Collision();
	void ChasePlayer();
	void ChaseUFO();
	void TurnOff();
	void LeavePlay();
};

