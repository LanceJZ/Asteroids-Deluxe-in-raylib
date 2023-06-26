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

	RockSize Size = Large;

	bool Initialize();
	void SetReferences(CrossCom& crossCom, std::shared_ptr<Player> thePlayer);
	void Update(float deltaTime);

	void Spawn(Vector3 pos, RockSize size);


private:
	std::shared_ptr<Player> ThePlayer;
	//std::shared_ptr<UFO> TheUFO;
	CrossCom* Com;

	void GiveScore();
	bool CheckCollision();
	void Hit();
};

