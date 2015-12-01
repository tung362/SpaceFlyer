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

EnemyMissileTurret::EnemyMissileTurret()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
	runOnce = true;
}

EnemyMissileTurret::EnemyMissileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 0.5f;
	shootTimer = 0;
	fireSpeed = 4.0f;
	runOnce = true;
}


EnemyMissileTurret::~EnemyMissileTurret()
{
}

void EnemyMissileTurret::Movement(GlobalData* gd)
{
	//If theres a target begin to rotate towards it
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

void EnemyMissileTurret::Shoot(GlobalData* gd)
{
	shootTimer += getDeltaTime();

	if (shootTimer >= fireSpeed)
	{
		//Spawn bullet
		EnemyMissile newProjectile((gd)->EnemyMissleTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 200, textureAngle, target);
		newProjectile.SetCollider(10, 10);
		(gd)->EnemyMissiles.push_back(newProjectile); //Adds to list

		shootTimer = 0;
	}
}

void EnemyMissileTurret::OnUpdateLogic(GlobalData* gd)
{
	if (runOnce == true)
	{
		//Assign player as target
		for (unsigned int i = 0; i < (gd)->PlayerMode2s.size(); ++i) target = &(gd)->PlayerMode2s[i];
		runOnce = false;
	}

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

void EnemyMissileTurret::ResetAll()
{
}
