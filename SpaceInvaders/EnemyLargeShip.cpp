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

EnemyLargeShip::EnemyLargeShip()
{
	position = Vector2(600, 40);
	SetTextureSettings(80.0f, 80.0f, 0, true);
	speed = 200;
	health = 1500;
	destroyed = false;
}

EnemyLargeShip::EnemyLargeShip(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(120.0f, 120.0f, 0, true);
	speed = newSpeed;
	rotationSpeed = 1.2f;
	ReverseRotation = false;
	health = 1500;
	destroyed = false;
	targetChangeTimer = 10;
	targetChangeDelay = 3;
	randomDelay = Randint(-0.5f, 0.5f);
	randomTargetPos = Vector2(0, 0);
	CreateShipParts(gd);
}

EnemyLargeShip::~EnemyLargeShip()
{
}

void EnemyLargeShip::CreateShipParts(GlobalData* gd)
{
	//Blasters
	EnemyBlasterTurret enemyBlasterTurret1((gd)->EnemyBlasterTurretTexture, 1, Vector2(position.x + 45, position.y + 13));
	Blasters.push_back(enemyBlasterTurret1);

	EnemyBlasterTurret enemyBlasterTurret2((gd)->EnemyBlasterTurretTexture, 1, Vector2(position.x + 45, position.y - 13));
	Blasters.push_back(enemyBlasterTurret2);

	//Missiles
	EnemyMissileTurret enemyMissileTurret1((gd)->EnemyMissleTurretTexture, 1, Vector2(position.x + 24, position.y + 0));
	Missiles.push_back(enemyMissileTurret1);

	EnemyMissileTurret enemyMissileTurret2((gd)->EnemyMissleTurretTexture, 1, Vector2(position.x - 16, position.y + 5));
	Missiles.push_back(enemyMissileTurret2);

	EnemyMissileTurret enemyMissileTurret3((gd)->EnemyMissleTurretTexture, 1, Vector2(position.x + 7, position.y + 10));
	Missiles.push_back(enemyMissileTurret3);

	EnemyMissileTurret enemyMissileTurret4((gd)->EnemyMissleTurretTexture, 1, Vector2(position.x + 5, position.y - 10));
	Missiles.push_back(enemyMissileTurret4);

	//Projectile
	EnemyProjectileTurret enemyProjectileTurret1((gd)->EnemyProjectileTurretTexture, 1, Vector2(position.x + 11, position.y - 21));
	Projectiles.push_back(enemyProjectileTurret1);

	EnemyProjectileTurret enemyProjectileTurret2((gd)->EnemyProjectileTurretTexture, 1, Vector2(position.x + 22, position.y - 17));
	Projectiles.push_back(enemyProjectileTurret2);

	EnemyProjectileTurret enemyProjectileTurret3((gd)->EnemyProjectileTurretTexture, 1, Vector2(position.x + 22, position.y + 17));
	Projectiles.push_back(enemyProjectileTurret3);

	EnemyProjectileTurret enemyProjectileTurret4((gd)->EnemyProjectileTurretTexture, 1, Vector2(position.x + 37, position.y - 19));
	Projectiles.push_back(enemyProjectileTurret4);

	EnemyProjectileTurret enemyProjectileTurret5((gd)->EnemyProjectileTurretTexture, 1, Vector2(position.x + 37, position.y + 19));
	Projectiles.push_back(enemyProjectileTurret5);

	//AntiProjectiles
	EnemyAntiProjectileTurret enemyAntiProjectileTurret1((gd)->EnemyAntiProjectileTurretTexture, 1, Vector2(position.x + 33, position.y + 8));
	AntiProjectiles.push_back(enemyAntiProjectileTurret1);

	EnemyAntiProjectileTurret enemyAntiProjectileTurret2((gd)->EnemyAntiProjectileTurretTexture, 1, Vector2(position.x + 33, position.y - 8));
	AntiProjectiles.push_back(enemyAntiProjectileTurret2);

	EnemyAntiProjectileTurret enemyAntiProjectileTurret3((gd)->EnemyAntiProjectileTurretTexture, 1, Vector2(position.x - 36, position.y - 18));
	AntiProjectiles.push_back(enemyAntiProjectileTurret3);

	EnemyAntiProjectileTurret enemyAntiProjectileTurret4((gd)->EnemyAntiProjectileTurretTexture, 1, Vector2(position.x - 17, position.y - 18));
	AntiProjectiles.push_back(enemyAntiProjectileTurret4);

	//Assigning Position Arrays
	for (unsigned int i = 0; i < Blasters.size(); ++i)
		BlasterX[i] = Blasters[i].GetPosition().x - position.x, BlasterY[i] = Blasters[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < Missiles.size(); ++i)
		MissileX[i] = Missiles[i].GetPosition().x - position.x, MissileY[i] = Missiles[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < Projectiles.size(); ++i)
		ProjectileX[i] = Projectiles[i].GetPosition().x - position.x, ProjectileY[i] = Projectiles[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < AntiProjectiles.size(); ++i)
		AntiProjectileX[i] = AntiProjectiles[i].GetPosition().x - position.x, AntiProjectileY[i] = AntiProjectiles[i].GetPosition().y - position.y;
}

void EnemyLargeShip::CalculateDirection(GlobalData* gd)
{
	forwardDirection = RotatePoint(0, 0, textureAngle, Vector2(forwardOrientation.x, forwardOrientation.y));
	rightSideDirection = RotatePoint(0, 0, textureAngle, Vector2(rightSideOrientation.x, rightSideOrientation.y));
	leftSideDirection = RotatePoint(0, 0, textureAngle, Vector2(leftSideOrientation.x, leftSideOrientation.y));

	//Blasters
	for (unsigned int i = 0; i < Blasters.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + BlasterX[i], position.y - BlasterY[i]));
		Blasters[i].SetPosition(newPos);
		Blasters[i].OnUpdateLogic(gd);
	}
	//Missiles
	for (unsigned int i = 0; i < Missiles.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + MissileX[i], position.y - MissileY[i]));
		Missiles[i].SetPosition(newPos);
		Missiles[i].OnUpdateLogic(gd);
	}
	//Projectiles
	for (unsigned int i = 0; i < Projectiles.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + ProjectileX[i], position.y - ProjectileY[i]));
		Projectiles[i].SetPosition(newPos);
		Projectiles[i].OnUpdateLogic(gd);
	}
	//AntiProjectile
	for (unsigned int i = 0; i < AntiProjectiles.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + AntiProjectileX[i], position.y - AntiProjectileY[i]));
		AntiProjectiles[i].SetPosition(newPos);
		AntiProjectiles[i].OnUpdateLogic(gd);
	}
}

void EnemyLargeShip::Destroy()
{
	destroyed = true;
}

bool EnemyLargeShip::isDestroyed()
{
	return destroyed;
}

void EnemyLargeShip::Movement(GlobalData* gd)
{
	targetChangeTimer += getDeltaTime();

	if (targetChangeTimer > targetChangeDelay + randomDelay)
	{
		randomTargetPos = Vector2(Randint(20.0f, 1180.0f), Randint(20.0f, 780.0f));
		randomDelay = Randint(-0.5f, 0.5f);
		targetChangeTimer = 0;
	}

	//Rotation
	Vector2 distance = randomTargetPos - position;
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

	Vector2 movement = Vector2(0, 0);
	float targetDistance = FindDistance(position, randomTargetPos);

	//If too far, get closer to player
	if (targetDistance > 100) movement = forwardDirection;

	//Apply movement
	position += (movement * speed) * getDeltaTime();
}

void EnemyLargeShip::OnUpdateLogic(GlobalData* gd)
{
	CalculateDirection(gd);

	//Displays directions and collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x, position.y, (position.x + forwardDirection.x * 70), position.y + (forwardDirection.y * 70));
		drawLine(position.x, position.y, (position.x + rightSideDirection.x * 70), position.y + (rightSideDirection.y * 70));
		drawLine(position.x, position.y, (position.x + leftSideDirection.x * 70), position.y + (leftSideDirection.y * 70));

		double radians = textureAngle * (PI / 180);
		double degrees = 180 * radians / PI;
		float colliderAngle;
		colliderAngle = (float)fmod(degrees, 180);

		Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
		Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
		Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
		Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

		drawLine(BottomRight.x, BottomRight.y, TopLeft.x, TopLeft.y);
		drawLine(BottomLeft.x, BottomLeft.y, TopRight.x, TopRight.y);
	}

	//Collision check
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		if (CollisionCheck<PlayerBullet>((gd)->PlayerBullets[i]) == true && (gd)->PlayerBullets[i].GetCanDamage() == true)
		{
			health -= 5;

			(gd)->PlayerBullets[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerMissiles.size(); ++i)
	{
		if (CollisionCheck<PlayerMissile>((gd)->PlayerMissiles[i]) == true && (gd)->PlayerMissiles[i].GetCanDamage() == true)
		{
			health -= 35;

			(gd)->PlayerMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstMissiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstMissile>((gd)->PlayerBurstMissiles[i]) == true && (gd)->PlayerBurstMissiles[i].GetCanDamage() == true)
		{
			health -= 18;

			(gd)->PlayerBurstMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->PlayerBurstProjectiles.size(); ++i)
	{
		if (CollisionCheck<PlayerBurstProjectile>((gd)->PlayerBurstProjectiles[i]) == true && (gd)->PlayerBurstProjectiles[i].GetCanDamage() == true)
		{
			health -= 5;

			(gd)->PlayerBurstProjectiles[i].SetCanDamage(false);
		}
	}

	//Death animation
	if (health <= 0)
	{

		SetTexture((gd)->EnemyShipExplodeTexture, 4);
		SetTextureSettings(120.0f, 120.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame)
		{
			int chance;
			chance = Randint(1, 5); //100% chance of anything dropping

									 //Powerup drops
			if (chance == 1)
			{
				Powerup newPowerup(1, (gd)->BlasterUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 2)
			{
				Powerup newPowerup(2, (gd)->BurstUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 3)
			{
				Powerup newPowerup(3, (gd)->EnergyReplenishUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 4)
			{
				Powerup newPowerup(4, (gd)->LifeUpMode2Texture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 5)
			{
				Powerup newPowerup(5, (gd)->MisslesUpTexture, 12, Vector2(position.x, position.y), 0, 0, Vector2(0, 0));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			Destroy();
		}
	}
	else
	{
		Movement(gd);
	}

	Animate();
}

template<typename T>
bool EnemyLargeShip::CollisionCheck(T & other)
{
	double radians = textureAngle * (PI / 180);
	double degrees = 180 * radians / PI;
	float colliderAngle;
	if (degrees >= 0) colliderAngle = (float)fmod(degrees, 180);
	else colliderAngle = (float)(180 + fmod(degrees, 180));

	//Gets enemy collider vertex
	float otherTop = other.GetPosition().y + other.GetCollider().height / 2;
	float otherBottom = other.GetPosition().y - other.GetCollider().height / 2;
	float otherRight = other.GetPosition().x + other.GetCollider().width / 2;
	float otherLeft = other.GetPosition().x - other.GetCollider().width / 2;

	//Gets EnemyLargeShip collider vertex (Position depends on the angle)
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

void EnemyLargeShip::ResetAll()
{
}
