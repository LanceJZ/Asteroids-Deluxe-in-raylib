#pragma once
#include <vector>
#include "raylib.h"

class CrossCom
{
public:
	bool rocksUnderFour = false;
	bool newWave = false;
	bool wedgeGroupActive = false;
	Vector3 wedgeGroupPos = {0};

	CrossCom();
	virtual ~CrossCom();

private:
};