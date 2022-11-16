#include "PositionedObject.h"

PositionedObject::PositionedObject()
{

}

void PositionedObject::Update(float deltaTime)
{
	Velocity.x += Acceleration.x;
	Velocity.y += Acceleration.y;
	X(X() + Velocity.x * deltaTime);
	Y(Y() + Velocity.y * deltaTime);

	RotationVelocity.z += RotationAcceleration.z;
	RotationZ += RotationVelocity.z * deltaTime;

	if (RotationZ > PI * 4)
	{
		RotationZ = 0;
	}
	else if (RotationZ < 0)
	{
		RotationZ = PI * 4;
	}

}

float PositionedObject::Chase(PositionedObject Chasing)
{
	return 0.0f;
}

float PositionedObject::RotateTowardsTargetZ(Vector3 target, float magnitude)
{
	return Common::RotateTowardsTargetZ(Position, target, RotationZ, magnitude);
}

float PositionedObject::AngleFromVectorsZ(Vector3 target)
{
	return (atan2f(target.y - Position.y, target.x - Position.x));
}

float PositionedObject::X()
{
	return Position.x;
}

float PositionedObject::Y()
{
	return Position.y;
}

float PositionedObject::Z()
{
	return Position.z;
}

void PositionedObject::X(float x)
{
	Position.x = x;
	Position2.x = x;
}

void PositionedObject::Y(float y)
{
	Position.y = y;
	Position2.y = y;
}

void PositionedObject::Z(float z)
{
	Position.z = z;
}

void PositionedObject::CheckScreenEdge()
{
	CheckScreenEdgeX();
	CheckScreenEdgeY();
}

void PositionedObject::CheckScreenEdgeX()
{
	if (X() > WindowWidth)
	{
		X(-WindowWidth);
	}

	if (X() < -WindowWidth)
	{
		X(WindowWidth);
	}
}

void PositionedObject::CheckScreenEdgeY()
{
	if (Y() > WindowHeight)
	{
		Y(-WindowHeight);
	}

	if (Y() < -WindowHeight)
	{
		Y(WindowHeight);
	}
}

bool PositionedObject::OffScreen()
{
	return OffScreenSide() || OffScreenTopBottom();
}

bool PositionedObject::OffScreenSide()
{
	if (X() > WindowWidth || X() < -WindowWidth)
	{
		return true;
	}

	return false;
}

bool PositionedObject::OffScreenTopBottom()
{
	if (Y() > WindowHeight || Y() < -WindowHeight)
	{
		return true;
	}

	return false;
}

