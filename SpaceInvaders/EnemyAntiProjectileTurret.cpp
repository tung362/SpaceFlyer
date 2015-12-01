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
using std::cin;
using std::cout;
using std::endl;

EnemyAntiProjectileTurret::EnemyAntiProjectileTurret()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
	target = nullptr;
}

EnemyAntiProjectileTurret::EnemyAntiProjectileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 2.0f;
	shootTimer = 0;
	fireSpeed = 0.2f;
	target = nullptr;
}


EnemyAntiProjectileTurret::~EnemyAntiProjectileTurret()
{
}

void EnemyAntiProjectileTurret::Movement(GlobalData* gd)
{

	float maxTargetDistance = 300; //Max distance to search for target
	target = nullptr;

	//Closest Enemy Small Ship
	for (unsigned int i = 0; i < (gd)->PlayerMissiles.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->PlayerMissiles[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			target = &(gd)->PlayerMissiles[i];
		}
	}
	if (target != nullptr && (target)->isDestroyed() == true) target = nullptr;

	//If theres a target begin to rotate towards it
	if (target != nullptr)
	{
		Vector2 distance = (target)->GetPosition() - position;

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

void EnemyAntiProjectileTurret::Shoot(GlobalData* gd)
{
	if (target != nullptr)
	{
		shootTimer += getDeltaTime();

		if (shootTimer >= fireSpeed)
		{
			//Spawn bullet
			EnemyBullet newProjectile2(1, (gd)->EnemyBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 800, textureAngle, forwardDirection);
			newProjectile2.SetCollider(10, 10);
			(gd)->EnemyBullets.push_back(newProjectile2); //Adds to list

			shootTimer = 0;
		}
	}
}

void EnemyAntiProjectileTurret::OnUpdateLogic(GlobalData* gd)
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

void EnemyAntiProjectileTurret::ResetAll()
{
}
