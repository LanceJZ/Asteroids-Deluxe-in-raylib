#pragma once
#include "raylib.h"
#include "PositionedObject.h"
#include "Common.h"

class Entity : public PositionedObject, public Common
{
public:
	//using PositionedObject::MaxSpeed;
	//using PositionedObject::Position;
	//using PositionedObject::RotationZ;
	//using PositionedObject::Rotation;
	//using PositionedObject::Velocity;
	//using PositionedObject::Acceleration;
	//using PositionedObject::Velocity2;
	//using PositionedObject::Acceleration2;
	//using PositionedObject::Position2;
	//using PositionedObject::ScreenWidth;
	//using PositionedObject::ScreenHeight;

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
	Vector3 VelocityFromAngleZ(float rotation, float magnitude);
	Vector3 VelocityFromAngleZ(float magnitude);

private:

};

