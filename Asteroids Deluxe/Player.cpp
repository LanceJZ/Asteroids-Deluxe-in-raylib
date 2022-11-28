#include "Common.h"
#include "Player.h"
#include "raymath.h"
#include <string>

Player::Player(float windowWidth, float windowHeight)
{
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	flame = new LineModel();
	shield = new LineModel();

	for (int i = 0; i < 4; i++)
	{
		shots[i] = new Shot(windowWidth, windowHeight);
	}
}

Player::~Player()
{
	UnloadSound(Sound01);
	UnloadSound(Sound02);
	UnloadSound(Sound03);
	UnloadSound(Sound04);
	UnloadSound(Sound05);
	UnloadSound(Sound06);
	UnloadSound(Sound07);
}

void Player::LoadModel(string shipmodel, string flamemodel, string shieldmodel, vector<Vector3> dotModel)
{
	LineModel::LoadModel(shipmodel);
	flame->LoadModel(flamemodel);
	shield->LoadModel(shieldmodel);

	for (int i = 0; i < 4; i++)
	{
		shots[i]->SetModel(dotModel);
	}
}

void Player::LoadSound(Sound fireS, Sound thrustS, Sound exp, Sound bonus, Sound shieldHit, Sound shieldOn,
	Sound spawn)
{
	Sound01 = fireS;
	Sound02 = thrustS;
	Sound03 = exp;
	Sound04 = bonus;
	Sound05 = shieldHit;
	Sound06 = shieldOn;
	Sound07 = spawn;

	SetSoundVolume(Sound01, 0.25f);
	SetSoundVolume(Sound02, 0.5f);
	SetSoundVolume(Sound03, 0.95f);
	SetSoundVolume(Sound04, 0.75f);
	SetSoundVolume(Sound05, 0.75f);
	SetSoundVolume(Sound06, 0.75f);
	SetSoundVolume(Sound07, 0.75f);
}

void Player::Initialize()
{
	MaxSpeed = 20;
	Radius = 0.6f;
	Enabled = false;
	shield->Enabled = false;

	flame->Scale = Scale;
	flame->Radius = 0.1f;
	flame->Enabled = false;

	for (int i = 0; i < 6; i++)
	{
		lines.push_back(new Line());
	}
}

void Player::Input()
{
	float velocityRotZ = 0.07666f;

	if (IsKeyDown(KEY_RIGHT))
	{
		RotationZ += velocityRotZ;
	}

	if (IsKeyDown(KEY_LEFT))
	{
		RotationZ -= velocityRotZ;
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
	PositionedObject::Update(deltaTime);
	Entity::CheckScreenEdge();

	flame->Position = Position;
	flame->RotationZ = RotationZ;
	flame->Update(deltaTime);

	shield->Position = Position;
	shield->Update(deltaTime);

	if (thrustOff)
	{
		ThrustOff(deltaTime);
	}
	else if (thrustOn && Enabled)
	{
		ThrustOn(deltaTime);
	}

	for (auto shot : shots)
	{
		shot->Update(deltaTime);
	}

	if (shield->Enabled)
	{
		if (shieldPower > 0)
		{
			shieldPower -= 10 * deltaTime;

			if (shieldPower < 0)
				shieldPower = 0;
		}
	}
	else
	{
		if (shieldPower < 100)
		{
			shieldPower += 1 * deltaTime;
		}
	}
}

void Player::Draw()
{
	LineModel::Draw();
	flame->Draw();
	shield->Draw();

	for (auto line : lines)
	{
		line->Draw();
	}

	for (auto shot : shots)
	{
		shot->Draw();
	}
}

void Player::Hit()
{
	StopSound(Sound02);
	PlaySound(Sound03);
	Enabled = false;
	thrustOff = true;
	thrustOn = false;
	exploding = true;
	flame->Enabled = false;
	shield->Enabled = false;
	Acceleration = { 0 };
	Velocity = { 0 };

	for (auto line : lines)
	{
		line->Spawn(Position);
	}


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
		PlaySound(Sound04);
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
	PlaySound(Sound07);

	Position = { 0, 0, 0 };
	Velocity = { 0, 0, 0 };
	Enabled = true;

	for (auto line : lines)
	{
		line->Clear();
	}
}

void Player::ThrustOn(float deltaTime)
{
	if (!IsSoundPlaying(Sound02))
	{
		PlaySound(Sound02);
	}

	float acceleration = 10.666f;
	float topaccel = 0.05f;
	Acceleration.x = ((cos(RotationZ) - (Velocity.x * topaccel)) * acceleration) * deltaTime;
	Acceleration.y = ((sin(RotationZ) - (Velocity.y * topaccel)) * acceleration) * deltaTime;
	thrustOff = false;
	flame->Enabled = true;
}

void Player::ThrustOff(float deltaTime)
{
	StopSound(Sound02);

	float deceleration = 0.5f;
	Acceleration.x = (-Velocity.x * deceleration) * deltaTime;
	Acceleration.y = (-Velocity.y * deceleration) * deltaTime;
	flame->Enabled = false;
}

void Player::Fire()
{
	float speed = 25.5f;

	for (auto shot : shots)
	{
		if (!shot->Enabled)
		{
			PlaySound(Sound01);
			shot->Spawn(Position, VelocityFromAngleZ(speed), 1.5f);
			break;
		}
	}
}

bool Player::ShieldHit(Vector3 hitbyPos, Vector3 hitbyVel)
{
	if (IsSoundPlaying(Sound05))
	{
		StopSound(Sound05);
	}

	if (shieldPower == 0 || !shield->Enabled)
	{
		Hit();
		return false;
	}

	PlaySound(Sound05);

	Acceleration = { 0 };
	Velocity.x = (Velocity.x * 0.1f) * -1;
	Velocity.y = (Velocity.y * 0.1f) * -1;
	Velocity.x = hitbyVel.x * 0.95f;
	Velocity.y = hitbyVel.y * 0.95f;
	Vector3 vel = VelocityFromAngleZ(AngleFromVectorsZ(hitbyPos, Position), 4.5f);
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
		if (!IsSoundPlaying(Sound06))
		{
			PlaySound(Sound06);
		}

		shield->Enabled = true;
		shield->Alpha = 2.55f * shieldPower;
	}
}

void Player::ShieldOff()
{
	StopSound(Sound06);

	shield->Enabled = false;
}

bool Player::GetShieldIsOn()
{
	return shield->Enabled;
}
