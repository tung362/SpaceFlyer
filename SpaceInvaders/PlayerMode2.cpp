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

PlayerMode2::PlayerMode2()
{
	position = Vector2(600, 40);
	SetTextureSettings(80.0f, 80.0f, 0, true);
	speed = 200;
	health = 100;
	maxHealth = health;
	shield = 100;
	maxShield = shield;
	shieldRechargeTimer = 0;
	shieldRechargeDelay = 0.5;
}

PlayerMode2::PlayerMode2(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(80.0f, 80.0f, 0, true);
	speed = newSpeed;
	rotationSpeed = 1.5f;
	ReverseRotation = false;
	health = 100;
	maxHealth = health;
	shield = 100;
	maxShield = shield;
	shieldRechargeTimer = 0;
	shieldRechargeDelay = 0.5;
	CreateShipParts(gd);
}

PlayerMode2::~PlayerMode2()
{
}

void PlayerMode2::CreateShipParts(GlobalData* gd)
{
	//Blasters
	PlayerBlasterTurret playerBlasterTurret1(1, (gd)->PlayerBlasterTurretTexture, 1, Vector2(position.x + 30, position.y - 2));
	Blasters.push_back(playerBlasterTurret1);

	PlayerBlasterTurret playerBlasterTurret2(1, (gd)->PlayerBlasterTurretTexture, 1, Vector2(position.x + 20, position.y + 4));
	Blasters.push_back(playerBlasterTurret2);

	PlayerBlasterTurret playerBlasterTurret3(1, (gd)->PlayerBlasterTurretTexture, 1, Vector2(position.x + 20, position.y - 6));
	Blasters.push_back(playerBlasterTurret3);

	PlayerBlasterTurret playerBlasterTurret4(1, (gd)->PlayerBlasterTurretTexture, 1, Vector2(position.x - 10, position.y + 9));
	Blasters.push_back(playerBlasterTurret4);

	PlayerBlasterTurret playerBlasterTurret5(1, (gd)->PlayerBlasterTurretTexture, 1, Vector2(position.x - 10, position.y - 11));
	Blasters.push_back(playerBlasterTurret5);

	//Missiles
	PlayerMissileTurret playerMissileTurret1(1, (gd)->PlayerMissleTurretTexture, 1, Vector2(position.x + 2, position.y + 20));
	Missiles.push_back(playerMissileTurret1);

	PlayerMissileTurret playerMissileTurret2(1, (gd)->PlayerMissleTurretTexture, 1, Vector2(position.x + 2, position.y - 22));
	Missiles.push_back(playerMissileTurret2);

	//Burst
	PlayerBurstTurret playerBurstTurret1(1, (gd)->PlayerBurstTurretTexture, 1, Vector2(position.x - 20, position.y + 7));
	Bursts.push_back(playerBurstTurret1);

	PlayerBurstTurret playerBurstTurret2(1, (gd)->PlayerBurstTurretTexture, 1, Vector2(position.x - 20, position.y - 9));
	Bursts.push_back(playerBurstTurret2);

	//Anti Projectile
	PlayerAntiProjectileTurret playerAntiProjectileTurret1((gd)->PlayerAntiProjectileTurretTexture, 1, Vector2(position.x + 10, position.y + 7));
	AntiProjectiles.push_back(playerAntiProjectileTurret1);

	PlayerAntiProjectileTurret playerAntiProjectileTurret2((gd)->PlayerAntiProjectileTurretTexture, 1, Vector2(position.x + 10, position.y - 9));
	AntiProjectiles.push_back(playerAntiProjectileTurret2);

	//Assigning Position Arrays
	for (unsigned int i = 0; i < Blasters.size(); ++i)
		BlasterX[i] = Blasters[i].GetPosition().x - position.x, BlasterY[i] = Blasters[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < Missiles.size(); ++i)
		MissileX[i] = Missiles[i].GetPosition().x - position.x, MissileY[i] = Missiles[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < Bursts.size(); ++i)
		BurstX[i] = Bursts[i].GetPosition().x - position.x, BurstY[i] = Bursts[i].GetPosition().y - position.y;

	for (unsigned int i = 0; i < AntiProjectiles.size(); ++i)
		AntiProjectileX[i] = AntiProjectiles[i].GetPosition().x - position.x, AntiProjectileY[i] = AntiProjectiles[i].GetPosition().y - position.y;
}

void PlayerMode2::CalculateDirection(GlobalData* gd)
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
	//Burst
	for (unsigned int i = 0; i < Bursts.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + BurstX[i], position.y - BurstY[i]));
		Bursts[i].SetPosition(newPos);
		Bursts[i].OnUpdateLogic(gd);
	}
	//Anti Projectile
	for (unsigned int i = 0; i < AntiProjectiles.size(); ++i)
	{
		Vector2 newPos = RotatePoint(position.x, position.y, textureAngle, Vector2(position.x + AntiProjectileX[i], position.y - AntiProjectileY[i]));
		AntiProjectiles[i].SetPosition(newPos);
		AntiProjectiles[i].OnUpdateLogic(gd);
	}
}

float PlayerMode2::GetMaxHealth()
{
	return maxHealth;
}

void PlayerMode2::SetMaxHealth(float newMaxHealth)
{
	maxHealth = newMaxHealth;
}

float PlayerMode2::GetShield()
{
	return shield;
}

void PlayerMode2::SetShield(float newShield)
{
	shield = newShield;
}

float PlayerMode2::GetMaxShield()
{
	return maxShield;
}

void PlayerMode2::SetMaxShield(float newMaxShield)
{
	maxShield = newMaxShield;
}

void PlayerMode2::Movement(GlobalData* gd)
{
	Vector2 movement = Vector2(0, 0);

	//Gets the direction of movement and limit how far the PlayerMode2 can move
	if (getKey(Keycode_A) == true) textureAngle += rotationSpeed; //Turn left
	if (getKey(Keycode_D) == true) textureAngle -= rotationSpeed; //Turn right

	if (getKey(Keycode_W) == true &&
		(position.x + forwardDirection.x * 70 > 0 && position.x + forwardDirection.x * 70 < 1200) &&
		(position.y + forwardDirection.y * 70 > 0 && position.y + forwardDirection.y * 70 < 800)) movement = forwardDirection; //Move forward
	if (getKey(Keycode_S) == true &&
		(position.x + -forwardDirection.x * 70 > 0 && position.x + -forwardDirection.x * 70 < 1200) &&
		(position.y + -forwardDirection.y * 70 > 0 && position.y + -forwardDirection.y * 70 < 800)) movement.x = -forwardDirection.x, movement.y = -forwardDirection.y; ////Move backward

	//Pause Menu
	if (getKey(Keycode_ESCAPE) == true) (gd)->CurrentGameLevel = M2Pause;

	//Apply movement
	position += (movement * speed) * getDeltaTime();
}

void PlayerMode2::OnUpdateLogic(GlobalData* gd)
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
	for (unsigned int i = 0; i < (gd)->EnemyBullets.size(); ++i)
	{
		if (CollisionCheck<EnemyBullet>((gd)->EnemyBullets[i]) == true && (gd)->EnemyBullets[i].GetCanDamage() == true)
		{
			//If the shield can't handle any more damage, then health takes damage
			if(shield < 4) health -= 5;
			else shield -= 5;

			(gd)->EnemyBullets[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->EnemyMissiles.size(); ++i)
	{
		if (CollisionCheck<EnemyMissile>((gd)->EnemyMissiles[i]) == true && (gd)->EnemyMissiles[i].GetCanDamage() == true)
		{
			//If the shield can't handle any more damage, then health takes damage
			if (shield < 4) health -= 25;
			else shield -= 25;

			(gd)->EnemyMissiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->EnemyProjectiles.size(); ++i)
	{
		if (CollisionCheck<EnemyProjectile>((gd)->EnemyProjectiles[i]) == true && (gd)->EnemyProjectiles[i].GetCanDamage() == true)
		{
			//If the shield can't handle any more damage, then health takes damage
			if (shield < 4) health -= 15;
			else shield -= 15;

			(gd)->EnemyProjectiles[i].SetCanDamage(false);
		}
	}
	for (unsigned int i = 0; i < (gd)->Powerups.size(); ++i)
	{
		if (CollisionCheck<Powerup>((gd)->Powerups[i]) == true && (gd)->Powerups[i].GetCanDamage() == true)
		{
			if ((gd)->Powerups[i].GetPowerupType() == 1) (gd)->BlasterUpgrade += 1; //Blaster up
			else if ((gd)->Powerups[i].GetPowerupType() == 2) (gd)->BurstUpgrade += 1; //Burst up
			else if ((gd)->Powerups[i].GetPowerupType() == 3) shield = maxShield; //Energy replenish
			else if ((gd)->Powerups[i].GetPowerupType() == 4) maxHealth += 25, health += 50, maxShield += 25, shield += maxShield; //Life up
			else if ((gd)->Powerups[i].GetPowerupType() == 5) (gd)->MissileUpgrade += 1; //Missile up
			(gd)->Powerups[i].SetCanDamage(false);
		}
	}

	//Limit caps
	if ((gd)->BlasterUpgrade > (gd)->MaxBlasterUpgrade) (gd)->BlasterUpgrade = (gd)->MaxBlasterUpgrade;
	if ((gd)->BurstUpgrade > (gd)->MaxBurstUpgrade) (gd)->BurstUpgrade = (gd)->MaxBurstUpgrade;
	if ((gd)->MissileUpgrade > (gd)->MaxMissileUpgrade) (gd)->MissileUpgrade = (gd)->MaxMissileUpgrade;

	//Health
	if (health > maxHealth) health = maxHealth;

	//Shield
	shieldRechargeTimer += getDeltaTime();
	if (shieldRechargeTimer > shieldRechargeDelay)
	{
		//Less
		if (shield < maxShield)
		{
			if (shield < 0) shield = 0;
			shield += 2;
		}

		//Greater
		if (shield > maxShield) shield = maxShield;
		shieldRechargeTimer = 0;
	}

	//Death animation
	if (health <= 0)
	{
		SetTexture((gd)->PlayerShipExplodeTexture, 4);
		SetTextureSettings(120.0f, 120.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame) (gd)->LoseGame = true;
	}
	else
	{
		Movement(gd);
	}

	Animate();
}

template<typename T>
bool PlayerMode2::CollisionCheck(T & other)
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

void PlayerMode2::ResetAll()
{
}
