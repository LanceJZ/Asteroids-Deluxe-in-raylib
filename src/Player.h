#pragma once
#include "Managers.h"
#include "Common.h"
#include "LineModel.h"
#include "Shot.h"

class Player : public LineModel
{
public:
	Player();
	virtual ~Player();

	bool NewLife = false;
	bool Exploding = false;
	bool GameOver = true;
	bool Debug = false;
	int Wave { 0 };
	int Score { 0 };
	int HighScore{ 0 };
	int Lives { 0 };

	LineModel* Flame = {};
	std::vector<Shot*> Shots;

	void SetManagersRef(Managers& man);
	void SetShipModelID(size_t modelID);
	void SetShotModelID(size_t modelID);
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
	size_t ShipModelID = 0;
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

