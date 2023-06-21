#pragma once
#include "LineModel.h"

class Rock : public LineModel
{
public:
	Rock();
	virtual ~Rock();

	bool Initialize();
	bool BeginRun();

	void Input();
	void Update(float deltaTime);
	void Draw();

private:

};
