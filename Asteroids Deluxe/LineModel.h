#pragma once
#include "Entity.h"
#include <vector>
#include <string>

class LineModel : public Entity
{
public:
	Color modelColor = WHITE;
	float Alpha = 255;

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Load();
	void LoadModel(string fileName);
	vector<Vector3> GetModel();
	void SetModel(vector<Vector3> lines);

	LineModel();
	virtual ~LineModel();

private:
	vector<Vector3> lines;
	vector<Vector3> ConvertStringToVector(string linesString);
};