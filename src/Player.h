#pragma once
#include "Managers.h"
#include "Common.h"
#include "LineModel.h"
#include "Shot.h"

class Player : public LineModel
{
public:
	virtual ~Player();

	bool NewLife = false;
	bool Exploding = false;
	bool GameOver = true;
	bool Debug = false;
	int wave { 0 };
	int score { 0 };
	int highScore{ 0 };
	int lives { 0 };
	std::shared_ptr<LineModel> Flame;
	std::vector<std::shared_ptr<Shot>> Shots;

	void SetManagerRef(Managers& man);
	bool Initialize(); //initialize
	void Input();
	void Update(float deltaTime);

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
	Managers* Man = {};

	void ThrustOn(float deltaTime);
	void ThrustOff(float deltaTime);
	void Fire();
	void ShieldOn();
	void ShieldOff();
	void Gamepad();
	void Keyboard();
};

