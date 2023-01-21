#pragma once
#include "Common.h"

class PositionedObject : public Common
{
public:
	bool isChild = false;
	bool isParent = false;
	float MaxSpeed = 0;
	float Radius = 0;
	float WindowWidth = 0;
	float WindowHeight = 0;
	float Rotation = 0;
	float RotationVelocity = 0;
	float RotationAcceleration = 0;
	Vector2 Acceleration2 = { 0 };
	Vector2 Velocity2 = { 0 };
	Vector2 Position2 = { 0 };
	//Vector2 RotationVelocity2 = { 0 };
	//Vector2 RotationAcceleration2 = { 0 };
	Vector3 Acceleration = { 0 };
	Vector3 Velocity = { 0 };
	Vector3 Position = { 0 };
	//Vector3 Rotation = { 0 };
	//Vector3 RotationVelocity = { 0 };
	//Vector3 RotationAcceleration = { 0 };
	Vector3 RotationAxis = { 0, 0, 1 };
	float Chase(PositionedObject Chasing);
	float RotateTowardsTargetZ(Vector3 target, float magnitude);
	float AngleFromVectorsZ(Vector3 target);
	float AngleFromVectorsZ(Vector3 origin, Vector3 target);
	float AngleFromVectorZ(Vector3 target);
	Vector3 RandomVelocity(float magnitude);
	Vector3 VelocityFromAngleZ(float magnitude);
	Vector3 VelocityFromAngleZ(float angle, float magnitude);
	PositionedObject* parent;

	PositionedObject();
	virtual void Update(float deltaTime);

	virtual float X();
	virtual float Y();
	virtual float Z();
	virtual void X(float x);
	virtual void Y(float y);
	virtual void Z(float z);

	void CheckScreenEdge();
	void CheckScreenEdgeX();
	void CheckScreenEdgeY();
	bool OffScreen();
	bool OffScreenSide();
	bool OffScreenTopBottom();
	void LeavePlay(float turnSpeed, float speed);
	void RotateVelocity(Vector3 position, float turnSpeed, float speed);

private:

};

