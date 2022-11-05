#include "WedgeControl.h"

WedgeControl::WedgeControl(float playScreenW, float playScreenH, Player* player, UFO* ufo, CrossCom* crosscom)
{
	GameScreenWidth = playScreenW;
	GameScreenHeight = playScreenH;
	WedgeControl::player = player;
	WedgeControl::crossCom = crosscom;
	spawnTimer = new Timer();
	wedgeGroup = new WedgeGroup(playScreenW, playScreenH, player, ufo);
}

WedgeControl::~WedgeControl()
{
}

bool WedgeControl::Initialise()
{
	wedgeGroup->Initialize();
	spawnTimer->Reset(3);

	return false;
}

void WedgeControl::Load()
{

}

void WedgeControl::LoadModel(string model)
{
	wedgeGroup->LoadModel(model);
}

void WedgeControl::Input()
{

}

void WedgeControl::Update(float deltaTime)
{
	wedgeGroup->Update(deltaTime);
	spawnTimer->Update(deltaTime);

	if (spawnTimer->Elapsed())
	{
		spawnTimer->Reset();

		if (crossCom->rocksUnderFour && ready)
		{
			SpawnGroup();
		}
		else if (!ready)
		{
			ready = true;
		}
	}
}

void WedgeControl::Draw()
{
	wedgeGroup->Draw();
}

void WedgeControl::SpawnGroup()
{
	/*      Velocity = Core.RandomVelocity(3);
			Y = Core.RandomMinMax(-Core.ScreenHeight, Core.ScreenHeight);
			X = Core.ScreenWidth;
	*/

	ready = false;
	crossCom->rocksUnderFour = false;

	if (wedgeGroup->Enabled)
	{
		spawnTimer->Reset();
		return;
	}

	wedgeGroup->Spawn({ GameScreenWidth,
		GetRandomFloat(-GameScreenHeight, GameScreenHeight), 0}, GetRandomVelocity(3));
}
