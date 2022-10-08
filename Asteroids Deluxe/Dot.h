#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Timer.h"

class Dot : public Entity
{
public:
	virtual void Update(float deltaTime);
	virtual void Draw();

	bool Initialise();

	void Spawn(Vector3 position, float time, float size);
	void Clear();

private:
	Timer* timer;
};

