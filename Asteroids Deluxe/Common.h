#pragma once
#include <vector>
#include <random>
#include "raylib.h"
#include "raymath.h"

using namespace std;

class Common
{
public:
	float GameScreenWidth = { 0 };
	float GameScreenHeight = { 0 };

	bool Initialize();
	float GetRandomScreenY();
	float GetRandomFloat(float min, float max);
	float GetRandomRadian();
	float AimAtTargetZ(Vector3 origin, Vector3 target, float facingAngle, float magnitude);
	float AngleFromVectorsZ(Vector3 origin, Vector3 target);
	Vector3 GetRandomVelocity(float speed);
	Vector3 GetRandomVelocity(float speed, float radianDirection);
	Vector3 GetVelocityFromAngleZ(float rotation, float magnitude);

private:
	random_device rd;
};

