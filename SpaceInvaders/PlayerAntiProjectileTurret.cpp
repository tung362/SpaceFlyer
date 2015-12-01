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

PlayerAntiProjectileTurret::PlayerAntiProjectileTurret()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
	targetID = 1;
	target1 = nullptr;
	target2 = nullptr;
}

PlayerAntiProjectileTurret::PlayerAntiProjectileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 2.0f;
	shootTimer = 0;
	fireSpeed = 0.2f;
	targetID = 1;
	target1 = nullptr;
	target2 = nullptr;
}


PlayerAntiProjectileTurret::~PlayerAntiProjectileTurret()
{
}

void PlayerAntiProjectileTurret::Movement(GlobalData* gd)
{

	float maxTargetDistance = 300; //Max distance to search for target

	if (target1 != nullptr) target1 = nullptr;
	if (target2 != nullptr) target2 = nullptr;

	//Closest Enemy Missile
	for (unsigned int i = 0; i < (gd)->EnemyMissiles.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->EnemyMissiles[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			targetID = 1;
			target1 = &(gd)->EnemyMissiles[i];
		}
	}
	if (target1 != nullptr && (target1)->isDestroyed() == true) target1 = nullptr;

	//Closest Enemy Projectile
	for (unsigned int i = 0; i < (gd)->EnemyProjectiles.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->EnemyProjectiles[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			targetID = 2;
			target2 = &(gd)->EnemyProjectiles[i];
		}
	}
	if (target2 != nullptr && (target2)->isDestroyed() == true) target2 = nullptr;

	//If theres a target begin to rotate towards it
	if (target1 != nullptr || target2 != nullptr)
	{
		Vector2 distance;
		if (targetID == 1) distance = (target1)->GetPosition() - position;
		else if (targetID == 2) distance = (target2)->GetPosition() - position;


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
	}
}

void PlayerAntiProjectileTurret::Shoot(GlobalData* gd)
{
	if (target1 != nullptr)
	{
		shootTimer += getDeltaTime();

		if (shootTimer >= fireSpeed)
		{
			//Spawn bullet
			PlayerBullet newProjectile((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection);
			newProjectile.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile); //Adds to list

			shootTimer = 0;
		}
	}
}

void PlayerAntiProjectileTurret::OnUpdateLogic(GlobalData* gd)
{
	CalculateDirection(gd);

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 15), position.y + (forwardDirection.y * 15));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 15), position.y + (rightSideDirection.y * 15));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 15), position.y + (leftSideDirection.y * 15));
	}

	Movement(gd);
	Shoot(gd);
	Animate();
}

void PlayerAntiProjectileTurret::ResetAll()
{
}
