#include "EntityMode2.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "sfwdraw.h"
#include "KeycodeInput.h"
#include "GlobalData.h"
#include "GameStruct.h"
#include <iostream>
#include <cstring>

using namespace sfw;

EnemySmallShip::EnemySmallShip()
{
	position = Vector2(600, 40);
	SetTextureSettings(80.0f, 80.0f, 0, true);
	speed = 200;
	health = 100;
	destroyed = false;
}

EnemySmallShip::EnemySmallShip(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(80.0f, 80.0f, 0, true);
	speed = newSpeed;
	rotationSpeed = 1.2f;
	ReverseRotation = false;
	health = 100;
	destroyed = false;
	CreateShipParts(gd);
}

EnemySmallShip::~EnemySmallShip()
{
}

void EnemySmallShip::CreateShipParts(GlobalData* gd)
{
	EnemyBlasterTurret enemyBlasterTurret1((gd)->EnemyBlasterTurretTexture, 1, Vector2(position.x - 5, position.y + 15));
	Blasters.push_back(enemyBlasterTurret1);

	EnemyBlasterTurret enemyBlasterTurret2((gd)->EnemyBlasterTurretTexture, 1, Vector2(position.x - 5, position.y - 15));
	Blasters.push_back(enemyBlasterTurret2);

	//Assigning Position Arrays
	for (unsigned int i = 0; i < Blasters.size(); ++i)
		BlasterX[i] = Blasters[i].GetPosition().x - position.x, BlasterY[i] = Blasters[i].GetPosition().y - position.y;
}

void EnemySmallShip::CalculateDirection(GlobalData* gd)
{
	forwardDirection = RotatePoint(0, 0, textureAngle, Vector2(forwardOrientation.x, forwardOrientation.y));
	rightSideDirection = RotatePoint(0, 0, textureAngle, Vector2(rightSideOrientation.x, rightSideOrientation.y));
	leftSideDirection = RotatePoint(0, 0, textureAngle, Vector2(leftSideOrientation.x, leftSideOrientation.y));

	//Blasters
	for (unsigned int i = 0; i < Blasters.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + BlasterX[i], position.y - BlasterY[i]));
		Blasters[i].SetPosition(newPos);
		Blasters[i].OnUpdateLogic(gd);
	}
}

void EnemySmallShip::Destroy()
{
	destroyed = true;
}

bool EnemySmallShip::isDestroyed()
{
	return destroyed;
}

void EnemySmallShip::Movement(GlobalData* gd)
{
	//Rotation
	Vector2 distance = (gd)->PlayerMode2s[0].GetPosition() - position;
	float radians = atan2f(distance.y, distance.x);
	double degrees = 180 * radians / PI;
	double goalAngle;
	if (degrees >= 0) goalAngle = degrees;
	else goalAngle = 360 + degrees;

	double theDistance = abs(textureAngle - goalAngle);

	//Slowly rotate to target
	if (theDistance > 1)
	{
		if (goalAngle > 180) //greater than 180
		{
			if (theDistance >= 180)
			{
				if (textureAngle <= 0) textureAngle = 360;
				textureAngle -= rotationSpeed;
			}
			else
			{
				if (textureAngle < goalAngle) textureAngle += rotationSpeed;
				else textureAngle -= rotationSpeed;
			}
		}
		else //less than 180
		{
			if (theDistance > 180)
			{
				if (textureAngle >= 360) textureAngle = 0;
				textureAngle += rotationSpeed;
			}
			else
			{
				if (textureAngle < goalAngle) textureAngle += rotationSpeed;
				else textureAngle -= rotationSpeed;
			}
		}
	}

	Vector2 movement = Vector2(0, 0);
	float targetDistance = FindDistance(position, (gd)->PlayerMode2s[0].GetPosition());

	//If too far, get closer to player
	if (targetDistance > 200) movement = forwardDirection;

	//Apply movement
	position += (movement * speed) * getDeltaTime();
}

void EnemySmallShip::OnUpdateLogic(GlobalData* gd)
{
	CalculateDirection(gd);

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 70), position.y + (forwardDirection.y * 70));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 70), position.y + (rightSideDirection.y * 70));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 70), position.y + (leftSideDirection.y * 70));

		double radians = textureAngle * (PI / 180);
		double degrees = 180 * radians / PI;
		float colliderAngle;
		colliderAngle = (float)fmod(degrees, 180);

		Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
		Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
		Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
		Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

		drawLine(BottomRight.x, BottomRight.y, TopLeft.x, TopLeft.y);
		drawLine(BottomLeft.x, BottomLeft.y, TopRight.x, TopRight.y);
	}

	//Collision check
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		if (CollisionCheck<PlayerBullet>((gd)->PlayerBullets[i]) == true && (gd)->PlayerBullets[i].GetCanDamage() == true)
		{
			health -= 5;

			(gd)->PlayerBullets[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerMissiles.size(); ++i)
	{
		if (CollisionCheck<PlayerMissile>((gd)->PlayerMissiles[i]) == true && (gd)->PlayerMissiles[i].GetCanDamage() == true)
		{
			health -= 35;

			(gd)->PlayerMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstMissiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstMissile>((gd)->PlayerBurstMissiles[i]) == true && (gd)->PlayerBurstMissiles[i].GetCanDamage() == true)
		{
			health -= 18;

			(gd)->PlayerBurstMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstProjectiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstProjectile>((gd)->PlayerBurstProjectiles[i]) == true && (gd)->PlayerBurstProjectiles[i].GetCanDamage() == true)
		{
			health -= 5;

			(gd)->PlayerBurstProjectiles[i].SetCanDamage(false);
		}
	}

	//Death animation
	if (health <= 0)
	{

		SetTexture((gd)->EnemyShipExplodeTexture, 4);
		SetTextureSettings(120.0f, 120.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame)
		{
			int chance;
			chance = Randint(1, 10); //50% chance of anything dropping

			//Powerup drops
			if (chance == 1)
			{
				Powerup newPowerup(1, (gd)->BlasterUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 2)
			{
				Powerup newPowerup(2, (gd)->BurstUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 3)
			{
				Powerup newPowerup(3, (gd)->EnergyReplenishUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 4)
			{
				Powerup newPowerup(4, (gd)->LifeUpMode2Texture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 5)
			{
				Powerup newPowerup(5, (gd)->MisslesUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			Destroy();
		}
	}
	else
	{
		Movement(gd);
	}

	Animate();
}

template<typename T>
bool EnemySmallShip::CollisionCheck(T & other)
{
	double radians = textureAngle * (PI / 180);
	double degrees = 180 * radians / PI;
	float colliderAngle;
	if (degrees >= 0) colliderAngle = (float)fmod(degrees, 180);
	else colliderAngle = (float)(180 + fmod(degrees, 180));

	//Gets enemy collider vertex
	float otherTop = other.GetPosition().y + other.GetCollider().height / 2;
	float otherBottom = other.GetPosition().y - other.GetCollider().height / 2;
	float otherRight = other.GetPosition().x + other.GetCollider().width / 2;
	float otherLeft = other.GetPosition().x - other.GetCollider().width / 2;

	//Gets EnemySmallShip collider vertex (Position depends on the angle)
	Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
	Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
	Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
	Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

																																																										 //Collision
	if (colliderAngle <= 90)
	{
		if (((otherTop <= TopLeft.y && otherTop >= BottomRight.y) || (otherBottom <= TopRight.y && otherBottom >= BottomLeft.y)) && //Top, Bottom
			((otherRight <= BottomRight.x && otherRight >= TopLeft.x) || (otherLeft <= BottomRight.x && otherLeft >= TopLeft.x))) return true; //Right, Left
		else return false;
	}
	else
	{
		if (((otherTop <= BottomRight.y && otherTop >= BottomLeft.y) || (otherBottom <= BottomRight.y && otherBottom >= TopLeft.y)) && //Top, Bottom
			((otherRight <= BottomLeft.x && otherRight >= TopRight.x) || (otherLeft <= BottomLeft.x && otherLeft >= TopRight.x))) return true; //Right, Left
		else return false;
	}
}

void EnemySmallShip::ResetAll()
{
}
