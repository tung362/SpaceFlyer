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

EnemyBullet::EnemyBullet()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 90, true);
	speed = 400;
	moveDirection = Vector2(0, 0);
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
}

EnemyBullet::EnemyBullet(int newBulletType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection)
{
	bulletType = newBulletType;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 40.0f, newAngle, true);
	speed = newSpeed;
	moveDirection = newMoveDirection;
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
}

EnemyBullet::~EnemyBullet()
{
}

void EnemyBullet::Destroy()
{
	destroyed = true;
}

bool EnemyBullet::isDestroyed()
{
	return destroyed;
}

int EnemyBullet::GetBulletType()
{
	return bulletType;
}

Vector2 EnemyBullet::GetMoveDirection()
{
	return moveDirection;
}

bool EnemyBullet::GetCanDamage()
{
	return canDamage;
}

void EnemyBullet::SetCanDamage(bool newCanDamage)
{
	canDamage = newCanDamage;
}

void EnemyBullet::Movement(GlobalData* gd)
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
		unsigned int hitTexture = (gd)->EnemyBulletHitTexture;
		if (bulletType == 1) hitTexture = (gd)->EnemyBulletHitTexture;
		else if (bulletType == 2) hitTexture = (gd)->EnemyBulletHitTexture2;
		else if (bulletType == 3) hitTexture = (gd)->EnemyBulletHitTexture3;

		SetTexture(hitTexture, 7);
		SetTextureSettings(70.0f, 70.0f, 0, true);
		SetFrameRate(0.03f);
		if (currentFrame == maxFrame) Destroy();
	}
}

void EnemyBullet::ResetAll()
{
}
