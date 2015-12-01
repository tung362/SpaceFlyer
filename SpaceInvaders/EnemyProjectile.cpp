#include "Entity.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "GameStruct.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;

EnemyProjectile::EnemyProjectile()
{
	position = Vector2(600, 40);
	SetTextureSettings(10.0f, 10.0f, 90, true);
	speed = 400;
	deathTimer = 0;
	rotationSpeed = 2.0f;
	destroyed = false;
	canDamage = true;
	runOnce = true;
	target = nullptr;
}

EnemyProjectile::EnemyProjectile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, PlayerMode2 * newTarget)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(10.0f, 10.0f, newAngle, true);
	speed = newSpeed;
	deathTimer = 0;
	rotationSpeed = 2.0f;
	destroyed = false;
	canDamage = true;
	runOnce = true;
	target = newTarget;
}

EnemyProjectile::~EnemyProjectile()
{
}

void EnemyProjectile::Destroy()
{
	destroyed = true;
}

bool EnemyProjectile::isDestroyed()
{
	return destroyed;
}

bool EnemyProjectile::GetCanDamage()
{
	return canDamage;
}

void EnemyProjectile::SetCanDamage(bool newCanDamage)
{
	canDamage = newCanDamage;
}

ColliderBounds EnemyProjectile::GetCollider()
{
	return collider;
}

void EnemyProjectile::Movement(GlobalData* gd)
{
	if (runOnce == true)
	{
		//Assign player as target
		for (unsigned int i = 0; i < (gd)->PlayerMode2s.size(); ++i) target = &(gd)->PlayerMode2s[i];
		runOnce = false;
	}

	CalculateDirection(gd);

	//Displays collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x - collider.width / 2, position.y, position.x + collider.width / 2, position.y);
		drawLine(position.x, position.y + collider.height / 2, position.x, position.y - collider.height / 2);
	}

	//Collision check
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		if (CollisionCheck<PlayerBullet>((gd)->PlayerBullets[i]) == true && (gd)->PlayerBullets[i].GetCanDamage() == true)
		{
			Destroy();

			(gd)->PlayerBullets[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstMissiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstMissile>((gd)->PlayerBurstMissiles[i]) == true && (gd)->PlayerBurstMissiles[i].GetCanDamage() == true)
		{
			Destroy();

			(gd)->PlayerBurstMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstProjectiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstProjectile>((gd)->PlayerBurstProjectiles[i]) == true && (gd)->PlayerBurstProjectiles[i].GetCanDamage() == true)
		{
			Destroy();

			(gd)->PlayerBurstProjectiles[i].SetCanDamage(false);
		}
	}

	if (canDamage == true) //Apply movement
	{
		if ((position.y <= 800 && position.y >= 0) && (position.x <= 1200 && position.x >= 0))
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
			position += (forwardDirection * speed) * getDeltaTime();
		}
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
template<typename T>
bool EnemyProjectile::CollisionCheck(T & other)
{
	double radians = textureAngle * (PI / 180);
	double degrees = 180 * radians / PI;
	float colliderAngle;
	if (ReverseRotation == false) colliderAngle = (float)fmod(degrees, 180);
	else colliderAngle = (float)(180 + fmod(degrees, 180));

	//Gets enemy collider vertex
	float otherTop = other.GetPosition().y + other.GetCollider().height / 2;
	float otherBottom = other.GetPosition().y - other.GetCollider().height / 2;
	float otherRight = other.GetPosition().x + other.GetCollider().width / 2;
	float otherLeft = other.GetPosition().x - other.GetCollider().width / 2;

	//Gets PlayerMode2 collider vertex (Position depends on the angle)
	Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
	Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
	Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
	Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

																																																										 //Collision
	if (colliderAngle <= 90)
	{
		if (((otherTop <= TopLeft.y && otherTop >= BottomRight.y) || (otherBottom <= TopRight.y && otherBottom >= BottomLeft.y)) && //Top, Bottom
			((otherRight <= BottomRight.x && otherRight >= TopLeft.x) || (otherLeft <= BottomRight.x && otherLeft >= TopLeft.x))) return true; //Right, Left
		else return false;
	}
	else
	{
		if (((otherTop <= BottomRight.y && otherTop >= BottomLeft.y) || (otherBottom <= BottomRight.y && otherBottom >= TopLeft.y)) && //Top, Bottom
			((otherRight <= BottomLeft.x && otherRight >= TopRight.x) || (otherLeft <= BottomLeft.x && otherLeft >= TopRight.x))) return true; //Right, Left
		else return false;
	}
}


void EnemyProjectile::ResetAll()
{
}
