#pragma once
#include "raylib.h"
#include "raymath.h"
#include "LineModel.h"
#include "Player.h"
#include "UFO.h"

class Wedge : public LineModel
{
public:
	bool docked = true;
	bool newWave = false;

	Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo);
	virtual ~Wedge();

	bool Initialize();
	void Load();

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

private:
	int score = 200;
	float rotateMagnitude = PI / 2;
	Player* player;
	//Color color = {175, 175, 255};

	bool CheckCollision();
	void Collision();
	void ChasePlayer();
};

