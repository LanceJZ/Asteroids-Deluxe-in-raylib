#include "PositionedObject.h"

PositionedObject::PositionedObject()
{

}

void PositionedObject::Update(float deltaTime)
{
	Velocity = Vector3Add(Velocity, Acceleration);
	Position = Vector3Add(Vector3Multiply({ deltaTime, deltaTime, deltaTime }, Velocity), Position);
	RotationVelocity += RotationAcceleration * deltaTime;
	Rotation += RotationVelocity * deltaTime;

	if (Rotation > PI * 4)
	{
		Rotation = 0;
	}
	else if (Rotation < 0)
	{
		Rotation = PI * 4;
	}
}

float PositionedObject::Chase(PositionedObject Chasing)
{
	return 0.0f;
}

float PositionedObject::RotateTowardsTargetZ(Vector3 target, float magnitude)
{
	return Common::RotateTowardsTargetZ(Position, target, Rotation, magnitude);
}

float PositionedObject::AngleFromVectorsZ(Vector3 target)
{
	return (atan2f(target.y - Position.y, target.x - Position.x));
}

float PositionedObject::AngleFromVectorsZ(Vector3 origin, Vector3 target)
{
	return (atan2(target.y - origin.y, target.x - origin.x));
}

float PositionedObject::AngleFromVectorZ(Vector3 target)
{
	return (float)atan2(target.y - Y(), target.x - X());
}

Vector3 PositionedObject::RandomVelocity(float magnitude)
{
	float ang = GetRandomFloat(0, PI * 2);

	return VelocityFromAngleZ(ang, magnitude);
}

Vector3 PositionedObject::VelocityFromAngleZ(float magnitude)
{
	return { (float)cos(Rotation) * magnitude,	(float)sin(Rotation) * magnitude, 0 };
}

Vector3 PositionedObject::VelocityFromAngleZ(float angle, float magnitude)
{
	return { (float)cos(angle) * magnitude, (float)sin(angle) * magnitude, 0 };
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

void PositionedObject::LeavePlay(float turnSpeed, float speed)
{
	float stageLeft = 0;

	if (Position.x > 0)
	{
		stageLeft = 60;
	}
	else
	{
		stageLeft = -60;
	}

	RotateVelocity({ stageLeft, Position.y, 0 }, turnSpeed, speed);
}

void PositionedObject::RotateVelocity(Vector3 position, float turnSpeed, float speed)
{
	RotationVelocity = RotateTowardsTargetZ(position, turnSpeed);
	Velocity = VelocityFromAngleZ(Rotation, speed);
}

