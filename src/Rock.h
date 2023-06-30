#pragma once
#include "CrossCom.h"
#include "LineModel.h"
#include "Player.h"
//#include "Exploder.h"
//#include "UFO.h"

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
	void SetReferences(CrossCom& com, std::shared_ptr<Player> thePlayer);
	void Update(float deltaTime);

	void Spawn(Vector3 pos, RockSize size);


private:
	std::shared_ptr<Player> ThePlayer;
	//std::shared_ptr<UFO> TheUFO;
	CrossCom* CC;

	void SendScoreToPlayer();
	bool CheckCollision();
	void Hit();
};

