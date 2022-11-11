#pragma once
#include "LineModel.h"
#include "Player.h"
#include "Shot.h"
#include "Exploder.h"
#include "Timer.h"

class UFO : public LineModel
{
public:
	enum Size
	{
		Small,
		Large
	};

	Size size;

	Shot* shot;
	Timer* fireTimer;
	Timer* vectorTimer;
	Exploder* exploder;

	UFO(float windowWidth, float windowHeight, Player* player);
	void LoadModel(string ship, vector<Vector3> dotModel);
	void LoadSound(Sound exp, Sound big, Sound small, Sound fire);
	bool Initialise();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 pos, Vector3 vel);
	void Collision();


private:
	float radius{ 0.9f };

	Player* player;

	void GiveScore();
	void ResetFireTimer();
	void ResetVectorTimer();
	void ChangeVector();
	void FireShot();
	bool CheckCollision();
	float AimedShot();
	bool CheckReachedSide();
};

