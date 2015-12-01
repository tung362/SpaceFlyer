#include "Entity.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "GameStruct.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

Powerup::Powerup()
{
	position = Vector2(600, 40);
	SetTextureSettings(23.0f, 23.0f, 90, true);
	speed = 400;
	moveDirection = Vector2(0, 0);
	deathTimer = 0;
	canDamage = true;
}

Powerup::Powerup(int newPowerupType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection)
{
	PowerupType = newPowerupType;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(23.0f, 23.0f, newAngle, true);
	speed = newSpeed;
	moveDirection = newMoveDirection;
	deathTimer = 0;
	canDamage = true;
}

Powerup::~Powerup()
{
}

void Powerup::Destroy()
{
	destroyed = true;
}

bool Powerup::isDestroyed()
{
	return destroyed;
}

Vector2 Powerup::GetMoveDirection()
{
	return moveDirection;
}

int Powerup::GetPowerupType()
{
	return PowerupType;
}

bool Powerup::GetCanDamage()
{
	return canDamage;
}

void Powerup::SetCanDamage(bool newCanDamage)
{
	canDamage = newCanDamage;
}

ColliderBounds Powerup::GetCollider()
{
	return collider;
}

void Powerup::Movement(GlobalData* gd)
{
	//Displays collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x - collider.width / 2, position.y, position.x + collider.width / 2, position.y);
		drawLine(position.x, position.y + collider.height / 2, position.x, position.y - collider.height / 2);
	}

	if (canDamage == true) //Apply movement
	{
		if ((position.y <= 800 && position.y >= 0) && (position.x <= 1200 && position.x >= 0)) position += (moveDirection * speed) * getDeltaTime();
		else destroyed = true;
	}
	else Destroy(); //Death animation
}

void Powerup::ResetAll()
{
}
