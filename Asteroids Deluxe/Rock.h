#pragma once
#include "LineModel.h"
#include "Player.h"
#include "UFO.h"
#include "Exploder.h"

class Rock : public LineModel
{
public:
	enum RockSize
	{
		Small,
		Medium,
		Large
	};

	RockSize size = Large;
	Exploder* exploder;

	Rock(float windowWidth, float windowHeight, Player* player, UFO* ufo);
	~Rock();
	void LoadSound(Sound exp);
	void SetDotModel(vector<Vector3> dotModel);
	bool Initialise();
	virtual void Update(float deltaTime);
	virtual void Draw();

	void Spawn(Vector3 pos, float speed, RockSize size);


private:
	void GiveScore();
	bool CheckCollision();
	Player* player;
	UFO* ufo;
	vector<Vector3> dotModel;
};

