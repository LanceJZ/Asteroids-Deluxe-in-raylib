#pragma once
#include "CrossCom.h"
#include "LineModel.h"
#include "Player.h"
#include "UFO.h"
//#include "Exploder.h"

class Rock : public LineModel
{
public:
	enum RockSize
	{
		Small,
		Medium,
		Large
	};

	virtual ~Rock();

	RockSize Size = Large;

	bool Debug = false;

	bool Initialize();
	void SetReferences(CrossCom& com, Player* player, UFO* ufo);
	void Update(float deltaTime);

	void Spawn(Vector3 pos, RockSize size);


private:
	Player* ThePlayer = {};
	UFO* TheUFO = {};
	CrossCom* CC = {};

	void SendScoreToPlayer();
	bool CheckCollision();
	void Hit();
};

