#include "Shot.h"

Shot::Shot(float windowWidth, float windowHeight)
{
	Enabled = false;
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;

	//Scale = 2.25f;
	Radius = 0.05f;

	timer = new Timer();

	LineModel::LoadModel(dotFile);
}

void Shot::LoadModel(Model model)
{
	//TheModel = model;
}

void Shot::Draw()
{
	LineModel::Draw();
}

void Shot::Update(float deltaTime)
{
	Entity::Update(deltaTime);
	timer->Update(deltaTime);
	CheckScreenEdge();

	if (timer->Elapsed())
	{
		Enabled = false;
	}
}

void Shot::Spawn(Vector3 pos, Vector3 vel, float timerAmount)
{
	Position = pos;
	Velocity = vel;
	Enabled = true;

	timer->Reset(timerAmount);
}