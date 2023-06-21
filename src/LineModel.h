#pragma once
#include "Entity.h"
#include "ContentManager.h"
#include <vector>
#include <string>

class LineModel : public Entity
{
public:
	Color ModelColor = WHITE;
	float Alpha = 255;

	virtual void Input();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void LoadModel(std::string fileName);

	LineModelPoints GetLineModel();
	std::vector<Vector3> GetModel();
	void SetModel(std::vector<Vector3> lines);
	void SetModel(LineModelPoints lines);

private:
	std::vector<Vector3> ConvertStringToVector(std::string linesString);
	void DrawLines(std::vector <Vector3> points, Vector3 rotationAxis, Color color);
	void DrawLines(Color color);
	std::vector<Vector3> LinePoints;
	LineModelPoints Lines;
};