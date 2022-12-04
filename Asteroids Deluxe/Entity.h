#pragma once
#include "PositionedObject.h"

class Entity : public PositionedObject
{
public:
	bool Enabled = true;
	bool BeenHit = false;
	float Scale = 1.0f;

	virtual float X();
	virtual float Y();
	virtual float Z();
	virtual void X(float x);
	virtual void Y(float y);
	virtual void Z(float z);

	Model TheModel;
	Sound Sound01;
	Sound Sound02;
	Sound Sound03;
	Sound Sound04;

	virtual void LoadModel(Model model);
	virtual void Update(float deltaTime);
	virtual void Draw();
	bool CirclesIntersect(Entity* target);

private:
};

