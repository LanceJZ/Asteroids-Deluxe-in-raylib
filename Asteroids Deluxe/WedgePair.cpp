#include "WedgePair.h"

WedgePair::WedgePair(float windowWidth, float windowHeight, Player* player, UFO* ufo)
{
	for (int i = 0; i < 2; i++)
	{
		wedges[i] = new Wedge(windowWidth, windowHeight, player, ufo);
	}

	WindowHeight = windowHeight;
	WindowWidth = windowWidth;
}

WedgePair::~WedgePair()
{
}

void WedgePair::LoadWedgeModel(vector<Vector3> model)
{
	wedgeModel.SetModel(model);

	for (auto wedge : wedges)
	{
		wedge->SetModel(wedgeModel.GetModel());
	}
}

bool WedgePair::Initialise()
{
	for (auto wedge : wedges)
	{
		wedge->Initialise();
	}

	wedgeDocked = true;

	return false;
}

void WedgePair::Load()
{

}

void WedgePair::LoadModel(string model)
{
}

void WedgePair::Input()
{

}

void WedgePair::Update(float deltaTime)
{
	Entity::Update(deltaTime);

	if (wedgeDocked)
	{
		Vector3 pos = VelocityFromAngleZ(RotationZ, 0.65f);

		wedges[1]->RotationZ = (float)PI + RotationZ;
		wedges[1]->X(Position.x - pos.x);
		wedges[1]->Y(Position.y - pos.y);
		wedges[0]->RotationZ = RotationZ;
		wedges[0]->X(pos.x + Position.x);
		wedges[0]->Y(pos.y + Position.y);
	}
	else
	{
		ChasePlayer();
	}

	for (auto wedge : wedges)
	{
		wedge->Update(deltaTime);
	}
}

void WedgePair::Draw()
{
	for (auto wedge : wedges)
	{
		wedge->Draw();
	}
}

void WedgePair::ChasePlayer()
{
	RotationVelocity.z = wedges[0]->ChasePlayer(this);
	Velocity = VelocityFromAngleZ(RotationZ, 5);
}