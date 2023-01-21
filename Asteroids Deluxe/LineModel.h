#pragma once
#include "Entity.h"
#include <vector>
#include <string>
#include "rlgl.h"

class LineModel : public Entity
{
public:
	Color ModelColor = WHITE;
	float Alpha = 255;

	virtual void Update(float deltaTime);
	virtual void Draw();
	virtual void AddChild(LineModel* child);
	virtual void AddChildren(LineModel* child);

	void Load();
	void LoadModel(string fileName);
	vector <LineModel*> children;
	vector <LineModel*> parents;

	vector<Vector3> GetModel();
	vector<Vector3> LinePoints;
	void SetModel(vector<Vector3> lines);

	LineModel();
	virtual ~LineModel();

private:
	vector<Vector3> ConvertStringToVector(string linesString);
	void DrawLines(vector <Vector3> points, Vector3 rotationAxis, Color color);
	void DrawLines(Color color);
};