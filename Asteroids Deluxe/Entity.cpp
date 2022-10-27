#include "Entity.h"
#include "raymath.h"

float Entity::X()
{
	return Position.x;
}

float Entity::Y()
{
	return Position.y;
}

float Entity::Z()
{
	return Position.z;
}

void Entity::X(float x)
{
	Position.x = x;
}

void Entity::Y(float y)
{
	Position.y = y;
}

void Entity::Z(float z)
{
	Position.z = z;
}

void Entity::LoadModel(Model model)
{
	TheModel = model;
}

void Entity::Update(float deltaTime)
{
	if (Enabled)
	{
		PositionedObject::Update(deltaTime);
		TheModel.transform = MatrixRotateZ(RotationZ);	// Rotate 3D model
	}
}

void Entity::Draw()
{
	if (Enabled)
	{
		DrawModel(TheModel, Position, Scale, RAYWHITE);	// Draw 3D model

#ifdef _DEBUG
		DrawCircle3D(Position, Radius, { 0 }, 0, { 150, 50, 200, 200 });
#endif
	}
}

/// <summary>
/// Circle collusion detection. Target circle will be compared to this class's.
/// Will return true of they intersect. Only for use with 2D Z plane.
/// </summary>
/// <param name="target">Target Positioned Object.</param>
/// <returns></returns>
bool Entity::CirclesIntersect(Entity* target)
{
	if (!Enabled || !target->Enabled)
		return false;

	Vector2 distance = { target->Position.x - X(), target->Position.y - Y() };
	float radius = Radius + target->Radius;

	if ((distance.x * distance.x) + (distance.y * distance.y) < radius * radius)
		return true;

	return false;
}

float Entity::AngleFromVectorZ(Vector3 target)
{
	return (float)atan2(target.y - Y(), target.x - X());
}

Vector3 Entity::VelocityFromAngleZ(float angle, float magnitude)
{
	return { (float)cos(angle) * magnitude,
				(float)sin(angle) * magnitude, 0 };
}

Vector3 Entity::VelocityFromAngleZ(float magnitude)
{
	return { (float)cos(RotationZ) * magnitude,
				(float)sin(RotationZ) * magnitude, 0 };
}

Vector3 Entity::RandomeVelocity(float magnitude)
{
	float ang = GetRandomFloat(0, PI * 2);

	return VelocityFromAngleZ(ang, magnitude);
}

float Entity::AngleFromVectorsZ(Vector3 origin, Vector3 target)
{
	return (atan2(target.y - origin.y, target.x - origin.x));
}
