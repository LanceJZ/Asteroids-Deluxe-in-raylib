#pragma once
#include "Managers.h"
#include "LineModel.h"
#include "Timer.h"

class Shot : public LineModel
{
public:
	void SetManagerRef(Managers& man);
	bool Initialize();
	void BeginRun();
	virtual void Update(float deltaTime);
	void Spawn(Vector3 pos, Vector3 vel, float timerAmount);

private:
	size_t ShotTimerNumber;
	float windowWidth;
	float windowHeight;
	Managers* Man = {};
};