#include "Player.h"

Player::~Player()
{
	delete Man;
}

void Player::SetManagersRef(Managers& man)
{
	Man = &man;
}

void Player::SetShipModelID(size_t modelID)
{
	ShipModelID = modelID;
	SetModel(Man->CM.GetLineModel(modelID));
}

void Player::SetShotModelID(size_t modelID)
{
	for (int i = 0; i < 4; i++)
	{
		Shots[i]->SetModel(Man->CM.GetLineModel(modelID));
	}
}

bool Player::Initialize()
{
	Entity::Initialize();

	Scale = 30;
	Flame->Scale = 30;
	Flame->Enabled = false;
	Flame->ModelColor = { 180, 180, 255, 255 };

	Radius = 16.5f;
	ModelColor = { 175, 175, 255, 255 };


	return true;
}

void Player::Input()
{
	Keyboard();

	if (IsGamepadAvailable(0))
	{
		Gamepad();
	}
}

void Player::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

	if (!ThrustIsOn)
	{
		ThrustOff(deltaTime);
	}
	else if (ThrustIsOn && Enabled)
	{
		ThrustOn(deltaTime);
	}

	CheckScreenEdge();
}

void Player::Hit()
{
	Enabled = false;
	ThrustIsOn = false;
	Exploding = true;
	Flame->Enabled = false;
	//Shield->Enabled = false;
	Acceleration = { 0 };
	Velocity = { 0 };


#ifdef _DEBUG
	if (!Debug)
		lives--;
#else
	lives--;
#endif
}

void Player::ScoreUpdate(int addToScore)
{
	score += addToScore;

	if (score > highScore)
	{
		highScore = score;
	}

	if (score > NextNewLifeScore)
	{
		NextNewLifeScore += 10000;
		lives++;
		NewLife = true;
	}
}

void Player::NewGame()
{
	lives = 4;
	NextNewLifeScore = 10000;
	score = 0;
	wave = 0;
	GameOver = false;
	Reset();
}

void Player::Reset()
{

	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;

	//for (auto line : lines)
	//{
	//	line->Clear();
	//}
}

void Player::ThrustOn(float deltaTime)
{
	Flame->Enabled = true;
	Acceleration = AccelerationToMaxAtRotation(240.666f, 0.001f, deltaTime);
}

void Player::ThrustOff(float deltaTime)
{
	Flame->Enabled = false;

	Acceleration = DecelerationToZero(0.45f, deltaTime);
}

void Player::Fire()
{
	float speed = 765.0f;
	float timer = 1.5f;

	for (auto shot : Shots)
	{
		if (!shot->Enabled)
		{
			shot->Spawn(Position, VelocityFromAngleZ(speed), timer);
			break;
		}
	}
}

bool Player::ShieldHit(Vector3 hitByPos, Vector3 hitByVel)
{
	//if (IsSoundPlaying(Thrust))
	//{
	//	StopSound(Thrust);
	//}

	if (ShieldPower == 0)// || !shield->Enabled)
	{
		Hit();
		return false;
	}


	Acceleration = { 0 };
	Velocity.x = (Velocity.x * 0.1f) * -1;
	Velocity.y = (Velocity.y * 0.1f) * -1;
	Velocity.x = hitByVel.x * 0.95f;
	Velocity.y = hitByVel.y * 0.95f;
	Vector3 vel = VelocityFromAngleZ(GetAngleFromVectorsZ(hitByPos, Position), 4.5f);
	Velocity.x += vel.x;
	Velocity.y += vel.y;

	if (ShieldPower > 20)
	{
		ShieldPower -= 20;
	}
	else
	{
		ShieldPower = 0;
	}

	return true;
}

void Player::ShieldOn()
{
	if (ShieldPower > 0)
	{
		//if (!IsSoundPlaying(ShieldSound))
		//{
		//	PlaySound(ShieldSound);
		//}

		//shield->Enabled = true;
		//shield->Alpha = 2.55f * shieldPower;
	}
}

void Player::ShieldOff()
{
	//StopSound(Sound06);

	//shield->Enabled = false;
}

void Player::Gamepad()
{
	//Button B is 6 for Shield //Button A is 7 for Fire //Button Y is 8 for Hyperspace
	//Button X is 5	//Left bumper is 9 //Right bumper is 11 for Shield //Left Trigger is 10
	//Right Trigger is 12 for Thrust //Dpad Up is 1 for	//Dpad Down is 3 for
	//Dpad Left is 4 for rotate left //Dpad Right is 2 for rotate right
	//Axis 1 is -1 for , 1 for  on left stick.
	//Axis 0 is -1 for Left, 1 for right on left stick.

	if (IsGamepadButtonDown(0, 12))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	float velocityRotZ = 0.07666f;

	if (IsGamepadButtonDown(0, 4) || GetGamepadAxisMovement(0, 0) < -0.25f)
	{
		Rotation -= velocityRotZ;
	}
	else if (IsGamepadButtonDown(0, 2) || GetGamepadAxisMovement(0, 0) > 0.25f)
	{
		Rotation += velocityRotZ;
	}

	if (IsGamepadButtonPressed(0, 7))
	{
		Fire();
	}

	if (IsGamepadButtonDown(0, 11) || IsGamepadButtonDown(0, 6))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}

void Player::Keyboard()
{
	float velocityRotZ = 3.666f;

	if (IsKeyDown(KEY_RIGHT))
	{
		RotationVelocity = velocityRotZ;
	}
	else if (IsKeyDown(KEY_LEFT))
	{
		RotationVelocity = -velocityRotZ;
	}
	else
	{
		RotationVelocity = 0;
	}

	if (IsKeyDown(KEY_UP))
	{
		ThrustIsOn = true;
	}
	else
	{
		ThrustIsOn = false;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) ||
		IsKeyPressed(KEY_SPACE))
	{
		Fire();
	}

	if (IsKeyDown(KEY_DOWN))
	{
		ShieldOn();
	}
	else
	{
		ShieldOff();
	}
}

bool Player::GetShieldIsOn()
{
	return false;// shield->Enabled;
}
