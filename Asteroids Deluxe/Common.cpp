#include "Common.h"

bool Common::Initialize()
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

float Common::AimAtTargetZ(Vector3 origin, Vector3 target, float facingAngle, float magnitude)
{
	float turnVelocity = 0;
	float targetAngle = AngleFromVectorsZ(origin, target);
	float targetLessFacing = targetAngle - facingAngle;
	float facingLessTarget = facingAngle - targetAngle;

	if (abs(targetLessFacing) > PI)
	{
		if (facingAngle > targetAngle)
		{
			facingLessTarget = (((PI *2) - facingAngle) + targetAngle) * -1;
		}
		else
		{
			facingLessTarget = ((PI * 2) - targetAngle) + facingAngle;
		}
	}

	if (facingLessTarget > 0)
	{
		turnVelocity = -magnitude;
	}
	else
	{
		turnVelocity = magnitude;
	}

	return turnVelocity;
}

float Common::AngleFromVectorsZ(Vector3 origin, Vector3 target)
{
	return (atan2(target.y - origin.y, target.x - origin.x));
}

Vector3 Common::GetRandomVelocity(float speed)
{
	return GetRandomVelocity(speed, GetRandomRadian();
}

Vector3 Common::GetRandomVelocity(float speed, float radianDirection)
{
	//  float amt = Core.RandomMinMax(speed * 0.15f, speed);
	//	return VelocityFromAngleZ(radianDirection, amt);


	return Vector3();
}

Vector3 Common::GetVelocityFromAngleZ(float rotation, float magnitude)
{
	//  return new Vector3(MathF.Cos(rotation) * magnitude,
	//	MathF.Sin(rotation)* magnitude, 0);

	return Vector3();
}
