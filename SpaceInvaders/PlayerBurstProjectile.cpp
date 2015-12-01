#include "Entity.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "GameStruct.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;

PlayerBurstProjectile::PlayerBurstProjectile()
{
	position = Vector2(600, 40);
	SetTextureSettings(10.0f, 10.0f, 90, true);
	speed = 400;
	moveDirection = Vector2(0, 0);
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
}

PlayerBurstProjectile::PlayerBurstProjectile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(10.0f, 10.0f, newAngle, true);
	speed = newSpeed;
	moveDirection = newMoveDirection;
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
}

PlayerBurstProjectile::~PlayerBurstProjectile()
{
}

void PlayerBurstProjectile::Destroy()
{
	destroyed = true;
}

bool PlayerBurstProjectile::isDestroyed()
{
	return destroyed;
}

Vector2 PlayerBurstProjectile::GetMoveDirection()
{
	return moveDirection;
}

bool PlayerBurstProjectile::GetCanDamage()
{
	return canDamage;
}

void PlayerBurstProjectile::SetCanDamage(bool newCanDamage)
{
	canDamage = newCanDamage;
}

ColliderBounds PlayerBurstProjectile::GetCollider()
{
	return collider;
}

void PlayerBurstProjectile::Movement(GlobalData* gd)
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
	else //Death animation
	{
		SetTexture((gd)->PlayerBulletHitTexture, 7);
		SetTextureSettings(70.0f, 70.0f, 0, true);
		SetFrameRate(0.03f);
		if (currentFrame == maxFrame) Destroy();
	}
}

void PlayerBurstProjectile::ResetAll()
{
}
