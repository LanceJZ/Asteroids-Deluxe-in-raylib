#pragma once
#include "Player.h"
#include "Entity.h"
#include "Shot.h"
#include "Exploder.h"
#include "Timer.h"

class UFO : public Entity
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

	void LoadModel(Model model, Model shotmodel);
	void LoadSound(Sound exp, Sound big, Sound small, Sound fire);
	virtual void Update(float deltaTime);
	virtual void Draw();
	bool Initialise();

	void Spawn(Vector3 pos, Vector3 vel);

	UFO(float windowWidth, float windowHeight, Player* player);

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

