#include "Exploder.h"

void Exploder::Update(float deltaTime)
{
	for (auto dot : dots)
	{
		dot->Update(deltaTime);
	}
}

void Exploder::Draw()
{
	for (auto dot : dots)
	{
		dot->Draw();
	}
}

bool Exploder::Initialise()
{
	return false;
}

void Exploder::Spawn(Vector3 position, int count, float radius)
{
	for (int i = 0; i < count; i++)
	{
		bool spawnDot = true;
		int dot = (int)dots.size();

		for (int c = 0; c < dot; c++)
		{
			if (!dots[c]->Enabled)
			{
				dot = c;
				spawnDot = false;
				break;
			}
		}

		if (spawnDot)
		{
			dots.push_back(new Dot());
			dots[dot]->Initialise();
		}

		dots[dot]->Spawn(position, count / 10.0f, radius / 2.0f);
	}
}

void Exploder::Clear()
{
	for (auto dot : dots)
	{
		dot->Enabled = false;
	}
}
