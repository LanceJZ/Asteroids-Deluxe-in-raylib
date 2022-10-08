#include "Line.h"
#include "raymath.h"

void Line::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	timer->Update(deltaTime);

	posStart = Vector3Add(startPos, Position);
	posEnd = Vector3Add(endPos, Position);

	if (timer->Elapsed())
	{
		Enabled = false;
	}
}

void Line::Draw()
{
	if (Enabled)
		DrawLine3D(posStart, posEnd, WHITE);
}

void Line::Load()
{

}

void Line::LoadModel(Model model, Model shotmodel)
{

}

void Line::Spawn(Vector3 pos)
{
	float size = 0.75f;
	Position = pos;
	Velocity = { GetRandomFloat(-size, size), GetRandomFloat(-size, size) , 0 };
	startPos = {GetRandomFloat(-size, size), GetRandomFloat(-size, size) , 0};
	endPos = { GetRandomFloat(-size, size), GetRandomFloat(-size, size) , 0 };

	Enabled = true;
	timer->Reset(GetRandomFloat(0.5f, 2.666f));
}

void Line::Clear()
{
	Enabled = false;
}

Line::Line()
{
	timer = new Timer();
	Enabled = false;
}

Line::~Line()
{
}