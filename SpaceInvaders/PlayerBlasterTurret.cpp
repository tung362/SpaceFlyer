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

PlayerBlasterTurret::PlayerBlasterTurret()
{
	workingAtUpgradeNum = 1;
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
}

PlayerBlasterTurret::PlayerBlasterTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	workingAtUpgradeNum = newWorkingAtUpgradeNum;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 2.0f;
	shootTimer = 0;
	fireSpeed = 0.3f;
}


PlayerBlasterTurret::~PlayerBlasterTurret()
{
}

void PlayerBlasterTurret::Movement(GlobalData* gd)
{
	Vector2 distance = Vector2(getMouseX(), getMouseY()) - position;
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

void PlayerBlasterTurret::Shoot(GlobalData* gd)
{
	if(shootTimer < fireSpeed) shootTimer += getDeltaTime();

	if (shootTimer >= fireSpeed && getMouseButton(MOUSE_BUTTON_RIGHT) == true)
	{
		//Spawn bullet
		PlayerBullet newProjectile((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection);
		newProjectile.SetCollider(10, 10);
		(gd)->PlayerBullets.push_back(newProjectile); //Adds to list

		if ((gd)->BlasterUpgrade == 2)
		{
			PlayerBullet newProjectile2((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.05f));
			newProjectile2.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile2); //Adds to list
		}
		else if ((gd)->BlasterUpgrade == 3)
		{
			PlayerBullet newProjectile2((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.05f));
			newProjectile2.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile2); //Adds to list

			PlayerBullet newProjectile3((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (leftSideDirection * 0.05f));
			newProjectile3.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile3); //Adds to list
		}
		else if ((gd)->BlasterUpgrade == 4)
		{
			PlayerBullet newProjectile2((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.05f));
			newProjectile2.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile2); //Adds to list

			PlayerBullet newProjectile3((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (leftSideDirection * 0.05f));
			newProjectile3.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile3); //Adds to list

			PlayerBullet newProjectile4((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.1f));
			newProjectile4.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile4); //Adds to list
		}
		else if ((gd)->BlasterUpgrade >= 5)
		{
			PlayerBullet newProjectile2((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.05f));
			newProjectile2.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile2); //Adds to list

			PlayerBullet newProjectile3((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (leftSideDirection * 0.05f));
			newProjectile3.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile3); //Adds to list

			PlayerBullet newProjectile4((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (rightSideDirection * 0.1f));
			newProjectile4.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile4); //Adds to list

			PlayerBullet newProjectile5((gd)->PlayerBulletTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 1000, textureAngle, forwardDirection + (leftSideDirection * 0.1f));
			newProjectile5.SetCollider(10, 10);
			(gd)->PlayerBullets.push_back(newProjectile5); //Adds to list
		}

		shootTimer = 0;
	}
}

void PlayerBlasterTurret::OnUpdateLogic(GlobalData* gd)
{
	CalculateDirection(gd);
	Movement(gd);
	Shoot(gd);
	Animate();

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 15), position.y + (forwardDirection.y * 15));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 15), position.y + (rightSideDirection.y * 15));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 15), position.y + (leftSideDirection.y * 15));
	}
}

void PlayerBlasterTurret::ResetAll()
{
}
