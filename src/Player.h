#pragma once
#include "Common.h"
#include "LineModel.h"
#include <vector>
#include <string>

class Player : public LineModel
{
public:
	bool paused = false;
	bool newLife = false;
	bool exploding = false;
	bool gameOver = true;
	bool debug = false;
	int wave { 0 };
	int score { 0 };
	int highScore{ 0 };
	int lives { 0 };

	//Shot* shots[4];
	//std::vector<Line*> lines;

	Player();
	~Player();
	bool Initialize(); //initialize
	void Input();
	void Update(float deltaTime);
	void Draw();

	void Hit();
	void ScoreUpdate(int addToScore);
	void NewGame();
	void Reset();
	bool GetShieldIsOn();
	bool ShieldHit(Vector3 hitbyPos, Vector3 hitbyVel);

private:
	bool thrustOff = true;
	bool thrustOn = false;
	int nextNewLifeScore = 10000;
	float thrustSoundTime = 0;
	float shieldPower = 100;
	Color color = WHITE;


	void ThrustOn(float deltaTime);
	void ThrustOff(float deltaTime);
	void Fire();
	void ShieldOn();
	void ShieldOff();
};

