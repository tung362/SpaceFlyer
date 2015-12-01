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

PlayerMissileTurret::PlayerMissileTurret()
{
	workingAtUpgradeNum = 1;
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
	targetID = 1;
	target1 = nullptr;
	target2 = nullptr;
	target3 = nullptr;
}

PlayerMissileTurret::PlayerMissileTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	workingAtUpgradeNum = newWorkingAtUpgradeNum;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 0.5f;
	shootTimer = 0;
	fireSpeed = 2.0f;
	targetID = 1;
	target1 = nullptr;
	target2 = nullptr;
	target3 = nullptr;
}


PlayerMissileTurret::~PlayerMissileTurret()
{
}

void PlayerMissileTurret::Movement(GlobalData* gd)
{
	
	float maxTargetDistance = 999999; //Max distance to search for target
	if (target1 != nullptr) target1 = nullptr;
	if (target2 != nullptr) target2 = nullptr;
	if (target3 != nullptr) target3 = nullptr;

	//Closest Enemy Small Ship
	for (unsigned int i = 0; i < (gd)->EnemySmallShips.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->EnemySmallShips[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			targetID = 1;
			target1 = &(gd)->EnemySmallShips[i];
		}
	}
	if (target1 != nullptr && (target1)->isDestroyed() == true) target1 = nullptr;

	//Closest Enemy Medium Ship
	for (unsigned int i = 0; i < (gd)->EnemyMediumShips.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->EnemyMediumShips[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			targetID = 2;
			target2 = &(gd)->EnemyMediumShips[i];
		}
	}
	if (target2 != nullptr && (target2)->isDestroyed() == true) target2 = nullptr;

	//Closest Enemy Large Ship
	for (unsigned int i = 0; i < (gd)->EnemyLargeShips.size(); ++i)
	{
		float distance = FindDistance(position, (gd)->EnemyLargeShips[i].GetPosition());
		if (distance < maxTargetDistance)
		{
			maxTargetDistance = distance;
			targetID = 3;
			target3 = &(gd)->EnemyLargeShips[i];
		}
	}
	if (target3 != nullptr && (target3)->isDestroyed() == true) target3 = nullptr;

	//If theres a target begin to rotate towards it
	if (target1 != nullptr || target2 != nullptr || target3 != nullptr)
	{
		Vector2 distance;
		if(targetID == 1) distance = (target1)->GetPosition() - position;
		else if (targetID == 2) distance = (target2)->GetPosition() - position;
		else if (targetID == 3) distance = (target3)->GetPosition() - position;


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

void PlayerMissileTurret::Shoot(GlobalData* gd)
{
	if (target1 != nullptr || target2 != nullptr || target3 != nullptr)
	{
		shootTimer += getDeltaTime();

		if (shootTimer >= fireSpeed)
		{
			if (targetID == 1)
			{
				//Spawn bullet
				PlayerMissile newProjectile((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle, 1, target1);
				newProjectile.SetCollider(10, 10);
				(gd)->PlayerMissiles.push_back(newProjectile); //Adds to list

				if ((gd)->MissileUpgrade >= 2)
				{
					PlayerMissile newProjectile2((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle + 135, 1, target1);
					newProjectile2.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile2); //Adds to list

					PlayerMissile newProjectile3((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle - 135, 1, target1);
					newProjectile3.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile3); //Adds to list
				}
			}
			else if (targetID == 2)
			{
				//Spawn bullet
				PlayerMissile newProjectile((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle, 2, target2);
				newProjectile.SetCollider(10, 10);
				(gd)->PlayerMissiles.push_back(newProjectile); //Adds to list

				if ((gd)->MissileUpgrade >= 2)
				{
					PlayerMissile newProjectile2((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle + 135, 2, target2);
					newProjectile2.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile2); //Adds to list

					PlayerMissile newProjectile3((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle - 135, 2, target2);
					newProjectile3.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile3); //Adds to list
				}
			}
			else if (targetID == 3)
			{
				//Spawn bullet
				PlayerMissile newProjectile((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle, 3, target3);
				newProjectile.SetCollider(10, 10);
				(gd)->PlayerMissiles.push_back(newProjectile); //Adds to list

				if ((gd)->MissileUpgrade >= 2)
				{
					PlayerMissile newProjectile2((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle + 135, 3, target3);
					newProjectile2.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile2); //Adds to list

					PlayerMissile newProjectile3((gd)->PlayerMissleTexture, 1, position + forwardDirection, 200, textureAngle - 135, 3, target3);
					newProjectile3.SetCollider(10, 10);
					(gd)->PlayerMissiles.push_back(newProjectile3); //Adds to list
				}
			}

			if ((gd)->MissileUpgrade >= 2) fireSpeed = 1.5f;

			shootTimer = 0;
		}
	}
}

void PlayerMissileTurret::OnUpdateLogic(GlobalData* gd)
{
	if ((gd)->MissileUpgrade >= workingAtUpgradeNum) CalculateDirection(gd), Movement(gd), Shoot(gd);
	Animate();

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 15), position.y + (forwardDirection.y * 15));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 15), position.y + (rightSideDirection.y * 15));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 15), position.y + (leftSideDirection.y * 15));
	}
}

void PlayerMissileTurret::ResetAll()
{
}
