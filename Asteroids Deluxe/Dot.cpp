#include "Dot.h"
#include "raymath.h"

void Dot::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	if (Enabled)
	{
		timer->Update(deltaTime);

		if (timer->Elapsed())
		{
			Enabled = false;
			Position = { NULL };
		}
	}
}

void Dot::Draw()
{
	//DrawPoint3D(Position, WHITE);
	if (Enabled)
		DrawCircle3D(Position, 0.02f, { 0 }, 0, WHITE);
}

bool Dot::Initialise()
{
	timer = new Timer();

	return false;
}

void Dot::Spawn(Vector3 position, float time, float size)
{
	Position = Vector3Add(position, { GetRandomFloat(-size, size), GetRandomFloat(-size, size),
		GetRandomFloat(-size, size) });

	float speed = 2.0f;

	Velocity = { GetRandomFloat(-speed, speed), GetRandomFloat(-speed, speed),
		GetRandomFloat(-speed, speed) };

	timer->Reset(GetRandomFloat(-time, time));
	Enabled = true;
}

void Dot::Clear()
{
	Enabled = false;
}
