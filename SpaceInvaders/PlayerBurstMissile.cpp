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

PlayerBurstMissile::PlayerBurstMissile()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 90, true);
	speed = 400;
	moveDirection = Vector2(0, 0);
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
	shootTimer = 0;
	fireSpeed = 0.5f;
}

PlayerBurstMissile::PlayerBurstMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(20.0f, 40.0f, newAngle, true);
	speed = newSpeed;
	moveDirection = newMoveDirection;
	deathTimer = 0;
	destroyed = false;
	canDamage = true;
	shootTimer = 0;
	fireSpeed = 0.5f;
}

PlayerBurstMissile::~PlayerBurstMissile()
{
}

void PlayerBurstMissile::Destroy()
{
	destroyed = true;
}

bool PlayerBurstMissile::isDestroyed()
{
	return destroyed;
}

Vector2 PlayerBurstMissile::GetMoveDirection()
{
	return moveDirection;
}

bool PlayerBurstMissile::GetCanDamage()
{
	return canDamage;
}

void PlayerBurstMissile::SetCanDamage(bool newCanDamage)
{
	canDamage = newCanDamage;
}

ColliderBounds PlayerBurstMissile::GetCollider()
{
	return collider;
}

void PlayerBurstMissile::Shoot(GlobalData * gd)
{
	shootTimer += getDeltaTime();

	if (shootTimer >= 1.3f)
	{
		//Spawn bullet
		PlayerBurstProjectile newProjectile((gd)->PlayerBurstProjectileTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 300, textureAngle, forwardDirection);
		newProjectile.SetCollider(10, 10);
		(gd)->PlayerBurstProjectiles.push_back(newProjectile); //Adds to list

		PlayerBurstProjectile newProjectile2((gd)->PlayerBurstProjectileTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 300, textureAngle, forwardDirection + (rightSideDirection * 0.1f));
		newProjectile2.SetCollider(10, 10);
		(gd)->PlayerBurstProjectiles.push_back(newProjectile2); //Adds to list

		PlayerBurstProjectile newProjectile3((gd)->PlayerBurstProjectileTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 300, textureAngle, forwardDirection + (leftSideDirection * 0.1f));
		newProjectile3.SetCollider(10, 10);
		(gd)->PlayerBurstProjectiles.push_back(newProjectile3); //Adds to list

		PlayerBurstProjectile newProjectile4((gd)->PlayerBurstProjectileTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 300, textureAngle, forwardDirection + (rightSideDirection * 0.2f));
		newProjectile4.SetCollider(10, 10);
		(gd)->PlayerBurstProjectiles.push_back(newProjectile4); //Adds to list

		PlayerBurstProjectile newProjectile5((gd)->PlayerBurstProjectileTexture, 1, Vector2(position.x + forwardDirection.x, position.y + forwardDirection.y), 300, textureAngle, forwardDirection + (leftSideDirection * 0.2f));
		newProjectile5.SetCollider(10, 10);
		(gd)->PlayerBurstProjectiles.push_back(newProjectile5); //Adds to list

		Destroy();
		shootTimer = 0;
	}
}

void PlayerBurstMissile::Movement(GlobalData* gd)
{
	CalculateDirection(gd);

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

		Shoot(gd);
	}
	else //Death animation
	{
		SetTexture((gd)->PlayerBulletHitTexture, 7);
		SetTextureSettings(70.0f, 70.0f, 0, true);
		SetFrameRate(0.03f);
		if (currentFrame == maxFrame) Destroy();
	}
}

void PlayerBurstMissile::ResetAll()
{
}
