#include "PositionedObject.h"

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

PositionedObject::PositionedObject()
{

}

void PositionedObject::Update(float deltaTime)
{
	Velocity.x += Acceleration.x;
	Velocity.y += Acceleration.y;
	X(X() + Velocity.x * deltaTime);
	Y(Y() + Velocity.y * deltaTime);

	if (RotationZ > PI * 4)
	{
		RotationZ = 0;
	}
	else if (RotationZ < 0)
	{
		RotationZ = PI * 4;
	}

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