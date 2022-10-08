#pragma once
#include "raylib.h"

class PositionedObject
{
public:
	float MaxSpeed{ 0 };
	float RotationZ{ 0 };
	float Radius{ 0 };
	float WindowWidth{ 0 };
	float WindowHeight{ 0 };
	Vector2 Acceleration2 = { 0 };
	Vector2 Velocity2 = { 0 };
	Vector2 Position2 = { 0 };
	Vector2 RotationVelocity2{ 0 };
	Vector2 RotationAcceleration2{ 0 };
	Vector3 Acceleration = { 0 };
	Vector3 Velocity = { 0 };
	Vector3 Position = { 0 };
	Vector3 Rotation = { 0 };
	Vector3 RotationVelocity = { 0 };
	Vector3 RotationAcceleration = { 0 };

	virtual float X();
	virtual float Y();
	virtual float Z();
	virtual void X(float x);
	virtual void Y(float y);
	virtual void Z(float z);

	PositionedObject();

	virtual void Update(float deltaTime);
	void CheckScreenEdge();
	void CheckScreenEdgeX();
	void CheckScreenEdgeY();

private:

};

