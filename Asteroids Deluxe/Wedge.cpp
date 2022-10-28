#include "Wedge.h"

Wedge::Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
	Wedge::player = player;
}

Wedge::~Wedge()
{
}

bool Wedge::Initialise()
{
	docked = true;

	return false;
}

void Wedge::Load()
{

}

void Wedge::Input()
{

}

void Wedge::Update(float deltaTime)
{
	LineModel::Update(deltaTime);
}

void Wedge::Draw()
{
	LineModel::Draw();
}

float Wedge::ChasePlayer(Entity* chaser)
{
	//return Core.AimAtTargetZ(origin, Main.instance.ThePlayer.Position, rotation, rotateMagnitude);

	return AimAtTargetZ(chaser->Position, player->Position, chaser->RotationZ, 5.0f);
}
