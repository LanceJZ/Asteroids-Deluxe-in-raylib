#pragma once
#include <vector>
#include "raylib.h"

class CrossCom
{
public:
	bool RockHit = false; //Trigger to check what rock was hit.
	bool WedgeHit = false; //Trigger to check what wedge was hit.
	bool SpawnWedgeGroup = false; //Trigger to spawn Wedge Group.
	bool NewWave = false; //Trigger for new wave to start.
	bool WedgeGroupActive = false; //Trigger to show at least one wedge is alive.
	Vector3 WedgeGroupPos = {0}; //To check Wedge Group Position.

private:
};