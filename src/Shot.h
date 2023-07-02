#pragma once
#include "Managers.h"
#include "LineModel.h"

class Shot : public LineModel
{
public:
	virtual ~Shot();

	void SetManagersRef(Managers& man);
	bool Initialize();
	bool BeginRun();
	virtual void Update(float deltaTime);
	void Spawn(Vector3 pos, Vector3 vel, float timerAmount);

private:
	size_t ShotTimerID;
	float windowWidth;
	float windowHeight;
	Managers* Man = {};
};