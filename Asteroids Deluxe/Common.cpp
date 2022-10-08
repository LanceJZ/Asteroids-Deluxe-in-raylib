#include "Common.h"

bool Common::Initialise()
{

	return false;
}

float Common::GetRandomScreenY()
{
	return GetRandomFloat(-GameScreenHeight, GameScreenHeight);
}

float Common::GetRandomFloat(float min, float max)
{
	default_random_engine eng(rd());
	uniform_real_distribution<float> distr(min, max);

	return distr(eng);
}

float Common::GetRandomRadian()
{
	return GetRandomFloat(0, PI * 2);
}
