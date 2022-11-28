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
	bool debug = false;
	int wave { 0 };
	int score { 0 };
	int highScore{ 0 };
	int lives { 0 };

	Shot* shots[4];
	vector<Line*> lines;

	Player(float windowWidth, float windowHeight);
	~Player();
	void LoadModel(string shipmodel, string flamemodel, string shieldmodel, vector<Vector3> dotModel);
	void LoadSound(Sound fireS, Sound thrustS, Sound exp, Sound bonus, Sound shieldHit, Sound shieldOn,
	Sound spawn);
	virtual void Initialize(); //initialize
	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Hit();
	void ScoreUpdate(int addToScore);
	void NewGame();
	void Reset();
	bool GetShieldIsOn();
	Vector3 ShieldHit(Vector3 hitbyPos, Vector3 hitbyVel);

private:
	bool thrustOff = true;
	bool thrustOn = false;
	int nextNewLifeScore = 10000;
	float thrustSoundTime = 0;
	float shieldPower = 100;
	Color color{ RAYWHITE };
	Sound Sound05;
	Sound Sound06;
	Sound Sound07;

	LineModel* flame;
	LineModel* shield;

	void ThrustOn(float deltaTime);
	void ThrustOff(float deltaTime);
	void Fire();
	void ShieldOn();
	void ShieldOff();
};

