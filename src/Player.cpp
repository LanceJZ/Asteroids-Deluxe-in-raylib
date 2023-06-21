#include "Player.h"

Player::Player()
{
}

Player::~Player()
{
}


bool Player::Initialize()
{
	Scale = 30;

	return true;
}

void Player::Input()
{
	float velocityRotZ = 0.07666f;

	if (IsKeyDown(KEY_RIGHT))
	{
		Rotation += velocityRotZ;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		Rotation -= velocityRotZ;
	}

	if (IsKeyDown(KEY_UP))
	{
		thrustOn = true;
		thrustOff = false;
	}
	else
	{
		thrustOn = false;
		thrustOff = true;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_SPACE))
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

void Player::Update(float deltaTime)
{
	LineModel::Update(deltaTime);

}

void Player::Draw()
{
	LineModel::Draw();

}

void Player::Hit()
{
	Enabled = false;
	thrustOff = true;
	thrustOn = false;
	exploding = true;
	//flame->Enabled = false;
	//shield->Enabled = false;
	Acceleration = { 0 };
	Velocity = { 0 };

	//for (auto line : lines)
	//{
	//	line->Spawn(Position);
	//}


#ifdef _DEBUG
	if (!debug)
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

	if (score > nextNewLifeScore)
	{
		nextNewLifeScore += 10000;
		lives++;
		newLife = true;
	}
}

void Player::NewGame()
{
	lives = 4;
	nextNewLifeScore = 10000;
	score = 0;
	wave = 0;
	gameOver = false;
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

	float acceleration = 10.666f;
	float topaccel = 0.05f;
	Acceleration.x = ((cos(Rotation) - (Velocity.x * topaccel)) * acceleration) * deltaTime;
	Acceleration.y = ((sin(Rotation) - (Velocity.y * topaccel)) * acceleration) * deltaTime;
	thrustOff = false;
	//flame->Enabled = true;
}

void Player::ThrustOff(float deltaTime)
{

	float deceleration = 0.5f;
	Acceleration.x = (-Velocity.x * deceleration) * deltaTime;
	Acceleration.y = (-Velocity.y * deceleration) * deltaTime;
	//flame->Enabled = false;
}

void Player::Fire()
{
	float speed = 25.5f;

	//for (auto shot : shots)
	//{
	//	if (!shot->Enabled)
	//	{
	//		shot->Spawn(Position, VelocityFromAngleZ(speed), 1.5f);
	//		break;
	//	}
	//}
}

bool Player::ShieldHit(Vector3 hitbyPos, Vector3 hitbyVel)
{
	//if (IsSoundPlaying(Thrust))
	//{
	//	StopSound(Thrust);
	//}

	if (shieldPower == 0)// || !shield->Enabled)
	{
		Hit();
		return false;
	}


	Acceleration = { 0 };
	Velocity.x = (Velocity.x * 0.1f) * -1;
	Velocity.y = (Velocity.y * 0.1f) * -1;
	Velocity.x = hitbyVel.x * 0.95f;
	Velocity.y = hitbyVel.y * 0.95f;
	Vector3 vel = VelocityFromAngleZ(GetAngleFromVectorsZ(hitbyPos, Position), 4.5f);
	Velocity.x += vel.x;
	Velocity.y += vel.y;

	if (shieldPower > 20)
	{
		shieldPower -= 20;
	}
	else
	{
		shieldPower = 0;
	}

	return true;
}

void Player::ShieldOn()
{
	if (shieldPower > 0)
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

bool Player::GetShieldIsOn()
{
	return false;// shield->Enabled;
}
