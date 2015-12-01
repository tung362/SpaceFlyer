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

PlayerBurstTurret::PlayerBurstTurret()
{
	workingAtUpgradeNum = 1;
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 20.0f, 0, true);
}

PlayerBurstTurret::PlayerBurstTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	workingAtUpgradeNum = newWorkingAtUpgradeNum;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 20.0f, 0, true);
	rotationSpeed = 1.3f;
	shootTimer = 0;
	fireSpeed = 1.3f;
}


PlayerBurstTurret::~PlayerBurstTurret()
{
}

void PlayerBurstTurret::Movement(GlobalData* gd)
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

void PlayerBurstTurret::Shoot(GlobalData* gd)
{
	if (shootTimer < fireSpeed) shootTimer += getDeltaTime();

	if (shootTimer >= fireSpeed && getMouseButton(MOUSE_BUTTON_RIGHT) == true)
	{
		//Spawn bullet
		PlayerBurstMissile newProjectile((gd)->PlayerBurstTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 200, textureAngle, forwardDirection);
		newProjectile.SetCollider(10, 10);
		(gd)->PlayerBurstMissiles.push_back(newProjectile); //Adds to list

		if ((gd)->BurstUpgrade >= 2) fireSpeed = 1.0f;

		shootTimer = 0;
	}
}

void PlayerBurstTurret::OnUpdateLogic(GlobalData* gd)
{
	if((gd)->BurstUpgrade >= workingAtUpgradeNum) CalculateDirection(gd), Movement(gd), Shoot(gd);
	Animate();

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 15), position.y + (forwardDirection.y * 15));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 15), position.y + (rightSideDirection.y * 15));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 15), position.y + (leftSideDirection.y * 15));
	}
}

void PlayerBurstTurret::ResetAll()
{
}
