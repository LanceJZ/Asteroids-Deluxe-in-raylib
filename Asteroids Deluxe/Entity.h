#pragma once
#include "raylib.h"
#include "PositionedObject.h"
#include "Common.h"

class Entity : public PositionedObject, public Common
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
	float AngleFromVectorZ(Vector3 target);
	Vector3 VelocityFromAngleZ(float magnitude);
	Vector3 VelocityFromAngleZ(float angle, float magnitude);
	Vector3 RandomeVelocity(float magnitude);
	float AngleFromVectorsZ(Vector3 origin, Vector3 target);
private:
};

