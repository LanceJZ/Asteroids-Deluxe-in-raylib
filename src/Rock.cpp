#include "Rock.h"

Rock::Rock()
{
}

Rock::~Rock()
{
}

bool Rock::Initialize()
{
	LineModel::Initialize();

	return false;
}

bool Rock::BeginRun()
{

	return false;
}

void Rock::Input()
{
	if (IsKeyPressed(KEY_UP))
	{
		Velocity.y += 1.5f;
	}
	else if (IsKeyPressed(KEY_DOWN))
	{
		Velocity.y -= 1.5f;
	}
}

void Rock::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	CheckScreenEdge();
}

void Rock::Draw()
{
	LineModel::Draw();

}
