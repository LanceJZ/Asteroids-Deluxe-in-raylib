#pragma once
#include "Wedge.h"
#include "Player.h"
#include "UFO.h"
#include "raylib.h"

class WedgePair : public Entity
{
public:
	bool docked = true;
	bool newWave = false;

	Wedge* wedges[2];

	WedgePair(float windowWidth, float windowHeight, Player* player, UFO* ufo);
	virtual ~WedgePair();

	bool Initialise();
	void Load();
	void LoadModel(string model);

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void LoadWedgeModel(vector<Vector3> model);

private:
	LineModel wedgeModel;

	void ChasePlayer();
};

