#pragma once
#include "raylib.h"
#include "Entity.h"
#include "Timer.h"

class Line : public Entity
{
public:
	Vector3 startPos = { 0 };
	Vector3 endPos = { 0 };
	Vector3 posStart = { 0 };
	Vector3 posEnd = { 0 };

	virtual void Update(float deltaTime);
	virtual void Draw();

	void Load();
	void LoadModel(Model model, Model shotmodel);
	void Spawn(Vector3 pos);
	void Clear();

	Line();
	virtual ~Line();

private:
	Timer* timer;
};

