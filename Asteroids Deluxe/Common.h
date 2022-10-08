#pragma once
#include <vector>
#include <random>
#include "raylib.h"
using namespace std;

class Common
{
public:
	float GameScreenWidth = { 0 };
	float GameScreenHeight = { 0 };

	bool Initialise();
	float GetRandomScreenY();
	float GetRandomFloat(float min, float max);
	float GetRandomRadian();

private:
	random_device rd;
};

