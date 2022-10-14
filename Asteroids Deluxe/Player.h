#pragma once
#include "LineModel.h"
#include "Shot.h"
#include "Line.h"
#include <vector>

class Player : public LineModel
{
public:
	bool paused = false;
	bool newLife = false;
	bool exploding = false;
	bool gameOver = true;
	int wave { 0 };
	int score { 0 };
	int highScore{ 0 };
	int lives { 0 };

	Shot* shots[4];
	vector<Line*> lines;

	Player(float windowWidth, float windowHeight);
	void LoadModel(string shipmodel, string flamemodel, string shieldmodel);
	void LoadSound(Sound fireS, Sound thrustS, Sound exp, Sound bonus);
	virtual void Initialize(); //initialize
	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Hit();
	void ScoreUpdate(int addToScore);
	void NewGame();
	void Reset();

private:
	int nextNewLifeScore = 10000;
	bool thrustOff = true;
	float thrustSoundTime = 0;
	float shieldPower = 100;
	Color color{ RAYWHITE };

	LineModel* flame;
	LineModel* shield;

	void ThrustOn();
	void ThrustOff(float deltaTime);
	void Fire();
	void ShieldOn();
	void ShieldOff();
};
