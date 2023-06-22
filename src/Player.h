#pragma once
#include "Common.h"
#include "LineModel.h"
#include <vector>
#include <string>

class Player : public LineModel
{
public:
	bool Paused = false;
	bool NewLife = false;
	bool Exploding = false;
	bool GameOver = true;
	bool Debug = false;
	int wave { 0 };
	int score { 0 };
	int highScore{ 0 };
	int lives { 0 };
	std::shared_ptr<LineModel> Flame;

	//Shot shots[4];
	//std::vector<Line*> lines;

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
	bool ThrustIsOn = false;
	int NextNewLifeScore = 10000;
	float ThrustSoundTime = 0;
	float ShieldPower = 100;
	Color TheColor = WHITE;

	void ThrustOn(float deltaTime);
	void ThrustOff(float deltaTime);
	void Fire();
	void ShieldOn();
	void ShieldOff();
};

