#include "Player.h"
#include "raymath.h"
#include <string>

Player::Player(float windowWidth, float windowHeight)
{
	WindowWidth = windowWidth;
	WindowHeight = windowHeight;
	MaxSpeed = 20;
	Radius = 0.6f;
	Enabled = false;

	flame = new LineModel();
	flame->Scale = Scale;
	flame->Radius = 0.1f;
	flame->Enabled = false;

	for (int i = 0; i < 4; i++)
	{
		shots[i] = new Shot(windowWidth, windowHeight);
	}

	for (int i = 0; i < 6; i++)
	{
		lines.push_back(new Line());
	}
}

void Player::LoadModel(string shipmodel, string flamemodel)
{
	LineModel::LoadModel(shipmodel);
	flame->LoadModel(flamemodel);
}

void Player::LoadSound(Sound fireS, Sound thrustS, Sound exp, Sound bonus)
{
	Sound01 = fireS;
	Sound02 = thrustS;
	Sound03 = exp;
	Sound04 = bonus;

	SetSoundVolume(Sound01, 0.25f);
	SetSoundVolume(Sound02, 0.5f);
	SetSoundVolume(Sound03, 0.5f);
	SetSoundVolume(Sound04, 0.75f);
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
		ThrustOn();
	}
	else
	{
		thrustOff = true;
	}

	if (IsKeyPressed(KEY_RIGHT_CONTROL) || IsKeyPressed(KEY_LEFT_CONTROL) || IsKeyPressed(KEY_SPACE))
	{
		Fire();
	}
}

void Player::Update(float deltaTime)
{
	PositionedObject::Update(deltaTime);
	Entity::CheckScreenEdge();

	flame->Position = Position;
	flame->RotationZ = RotationZ;
	flame->Update(deltaTime);

	if (thrustOff)
	{
		ThrustOff(deltaTime);
	}

	for (auto shot : shots)
	{
		shot->Update(deltaTime);
	}
}

void Player::Draw()
{
	LineModel::Draw();
	flame->Draw();

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
	//PlaySound(Sound03);
	//StopSound(Sound02);

	BeenHit = true;
	Enabled = false;
	thrustOff = true;
	lives--;
	exploding = true;

	flame->Enabled = false;

	for (auto line : lines)
	{
		line->Spawn(Position);
	}
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
		//PlaySound(Sound04);
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
	BeenHit = false;
	Enabled = true;

	for (auto line : lines)
	{
		line->Clear();
	}
}

void Player::ThrustOn()
{
	//if (!IsSoundPlaying(Sound02))
	//{
	//	PlaySound(Sound02);
	//}

	float acceleration = 0.25f;
	Acceleration.x = (cos(RotationZ) * acceleration);
	Acceleration.y = (sin(RotationZ) * acceleration);
	thrustOff = false;
	flame->Enabled = true;
}

void Player::ThrustOff(float deltaTime)
{
	float deceleration = 0.5f;
	Acceleration.x = (-Velocity.x * deceleration) * deltaTime;
	Acceleration.y = (-Velocity.y * deceleration) * deltaTime;
	flame->Enabled = false;
}

void Player::Fire()
{
	float speed = 25.5f;
	Vector3 velocity = { ((float)cos(RotationZ) * speed), ((float)sin(RotationZ) * speed), 0 };

	for (auto shot : shots)
	{
		if (!shot->Enabled)
		{
			//PlaySound(Sound01);
			shot->Spawn(Position, velocity, 1.5f);
			break;
		}
	}
}