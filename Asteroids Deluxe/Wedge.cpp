#include "Wedge.h"

Wedge::Wedge(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	WindowHeight = windowHeight;
	WindowWidth = windowWidth;

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
