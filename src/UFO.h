#pragma once
#include "LineModel.h"
#include "Managers.h"
#include "Player.h"
#include "Shot.h"
#include "Exploder.h"
#include "CrossCom.h"

class UFO : public LineModel
{
public:
	enum Size
	{
		Small,
		Large
	};

	Size size = Large;

	std::shared_ptr<Shot> TheShot;

	UFO();
	~UFO();
	bool Initialize();
	void SetPlayerRef(std::shared_ptr<Player> player);
	void SetCrossRef(CrossCom& com);
	void SetManagerRef(Managers& man);
	bool BeginRun();
	void Update(float deltaTime);
	void Draw();

	void Spawn(int spawnCount);
	void Collision();


private:
	size_t FireTimerID = 0;
	size_t ChangeVectorTimerID = 0;

	CrossCom* CC = {};
	Managers* Man = {};
	std::shared_ptr<Player> ThePlayer;

	void GiveScore();
	void ResetFireTimer();
	void ResetVectorTimer();
	void ChangeVector();
	void FireShot();
	float AimedShot();
	float AimedShotAtWGroup();
	float AimedShotAtRock();
	bool CheckCollision();
	bool CheckReachedSide();
};

