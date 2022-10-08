#pragma once
#include "Entity.h"
#include "Timer.h"

class Shot : public Entity
{
public:
	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void LoadModel(Model model);
	void Spawn(Vector3 pos, Vector3 vel, float timerAmount);

	Shot(float windowWidth, float windowHeight);

private:
	float windowWidth;
	float windowHeight;
	Color color{ RAYWHITE };
	Timer* timer;
};