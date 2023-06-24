#pragma once
#include "LineModel.h"
#include "Player.h"
#include "Shot.h"
#include "Exploder.h"
#include "Timer.h"
#include "CrossCom.h"
#include "RockData.h"

class UFO : public LineModel
{
public:
	enum Size
	{
		Small,
		Large
	};

	Size size = Large;

	Shot* shot;
	Timer* fireTimer;
	Timer* vectorTimer;
	Exploder* exploder;
	std::vector<RockData*> rocks;

	UFO(float windowWidth, float windowHeight, Player* player, CrossCom* crossCom, Color color);
	~UFO();
	void LoadModel(std::string ship, std::vector<Vector3> dotModel);
	void LoadSound(Sound exp, Sound big, Sound small, Sound fire);
	bool Initialise();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 pos, Vector3 vel);
	void Collision();


private:
	float radius{ 0.9f };

	Player* player;
	CrossCom* crossCom;
	Color color = WHITE;

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

