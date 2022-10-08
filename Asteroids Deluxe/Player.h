#pragma once
#include "Entity.h"
#include "Shot.h"
#include "Line.h"
#include <vector>

class Player : public Entity
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

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Hit();
	void ScoreUpdate(int addToScore);
	void NewGame();
	void Reset();
	void LoadModel(Model model, Model shotmodel, Model flamemodel);
	void LoadSound(Sound fireS, Sound thrustS, Sound exp, Sound bonus);
	Player(float windowWidth, float windowHeight);

private:
	int nextNewLifeScore{ 10000 };
	bool thrustOff = true;
	float thrustSoundTime = { 0 };
	Color color{ RAYWHITE };

	Entity* flame;

	void ThrustOn();
	void ThrustOff(float deltaTime);
	void Fire();
};

