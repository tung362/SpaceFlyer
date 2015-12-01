#include "Entity.h"
#include "GameFunction.h"
#include "GameObject.h"
#include "sfwdraw.h"
#include "KeycodeInput.h"
#include "GlobalData.h"
#include "GameStruct.h"
#include <iostream>
#include <cstring>

using namespace sfw;

Alien::Alien()
{
	position = Vector2(600, 40);
	SetTextureSettings(100.0f, 100.0f, 270, true);
	speed = 800;
	fireSpeed = 4;
	randomFireSpeed = Randint(-0.5f, 0.5f);
	fireTimer = 0;
	destroyed = false;
	alienType = 1;
	moveRight = true;
	moveDownSwitch = true;

	health = 1;
	if (health == 1) //Skips the flashes and in invincibility it only has 1 health
	{
		invincibilityTimer = 0;
		invincibilityDuration = 0;
		isInvincible = false;
		flashTimer = 0;
		flashDuration = 0;
		flash = false;
	}
	else
	{
		invincibilityTimer = 0;
		invincibilityDuration = 0.8f;
		isInvincible = false;
		flashTimer = 0;
		flashDuration = 0.3f;
		flash = false;
	}
}

Alien::Alien(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, int newAlienType)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(100.0f, 100.0f, 270, true);
	speed = newSpeed;
	rotationSpeed = 0;
	ReverseRotation = false;
	randomFireSpeed = Randint(-0.5f, 0.5f);
	fireTimer = 0;
	destroyed = false;
	alienType = newAlienType;
	moveRight = true;
	moveDownSwitch = true;

	if(alienType == 1) health = 1, fireSpeed = 4;
	else if (alienType == 2) health = 3, fireSpeed = 3.5f;
	else if (alienType == 3) health = 5, fireSpeed = 3;

	if (health == 1) //Skips the flashes and in invincibility it only has 1 health
	{
		invincibilityTimer = 0;
		invincibilityDuration = 0;
		isInvincible = false;
		flashTimer = 0;
		flashDuration = 0;
		flash = false;
	}
	else
	{
		invincibilityTimer = 0;
		invincibilityDuration = 0.8f;
		isInvincible = false;
		flashTimer = 0;
		flashDuration = 0.3f;
		flash = false;
	}
}

Alien::~Alien()
{
}

void Alien::Destroy()
{
	destroyed = true;
}

bool Alien::isDestroyed()
{
	return destroyed;
}

float Alien::GetInvincibilityDuration()
{
	return invincibilityDuration;
}

void Alien::SetInvincibilityDuration(float newInvincibilityDuration)
{
	invincibilityDuration = newInvincibilityDuration;
}

bool Alien::GetIsInvincible()
{
	return isInvincible;
}

void Alien::SetIsInvincible(bool newIsInvincible)
{
	isInvincible = newIsInvincible;
}

void Alien::Movement(GlobalData* gd)
{
	Vector2 movement = Vector2(0, 0);

	//Left
	if (moveRight == false && position.x - (textureWidth / 2) > 0)
	{
		if((gd)->AlienMove == true) movement.x = -1;
	}
	else
	{
		//Moves down
		if (moveDownSwitch == true && (gd)->AlienMove == true)
		{
			movement.y = -2;
			moveDownSwitch = false;
		}
		moveRight = true;
	}

	//Right
	if (moveRight == true && position.x + (textureWidth / 2) < 1200)
	{
		if((gd)->AlienMove == true) movement.x = 1;
	}
	else
	{
		//Moves down
		if (moveDownSwitch == false && (gd)->AlienMove == true)
		{
			movement.y = -2;
			moveDownSwitch = true;
		}
		moveRight = false;
	}

	//Lose
	if (position.y <= 100) (gd)->LoseGame = true;

	//Apply movement
	position += (movement * speed);
}

void Alien::Shoot(GlobalData* gd)
{
	fireTimer += getDeltaTime();
	if (fireTimer >= fireSpeed + randomFireSpeed)
	{
		unsigned int BulletTexture = (gd)->EnemyBulletTexture;
		int bulletType = 1;
		if (alienType == 1) bulletType = 1, BulletTexture = (gd)->EnemyBulletTexture;
		else if (alienType == 2) bulletType = 2, BulletTexture = (gd)->EnemyBulletTexture2;
		else if (alienType == 3) bulletType = 3, BulletTexture = (gd)->EnemyBulletTexture3;

		//Spawn bullet
		EnemyBullet newProjectile2(bulletType, BulletTexture, 1, Vector2(position.x, position.y - 20), 800, -90, Vector2(0, -1));
		newProjectile2.SetCollider(10, 10);
		(gd)->EnemyBullets.push_back(newProjectile2); //Adds to list
		randomFireSpeed = Randint(-0.5f, 0.5f);
		fireTimer = 0;
	}
}

void Alien::OnUpdateLogic(GlobalData* gd)
{
	//Displays collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x - collider.width / 2, position.y, position.x + collider.width / 2, position.y);
		drawLine(position.x, position.y + collider.height / 2, position.x, position.y - collider.height / 2);
	}

	//cout << "UP" << endl;

	//Collision check
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		if (CollisionCheck<PlayerBullet>((gd)->PlayerBullets[i]) == true && (gd)->PlayerBullets[i].GetCanDamage() == true)
		{
			if (isInvincible == false)
			{
				health -= 1;
				isInvincible = true;
			}
			(gd)->PlayerBullets[i].SetCanDamage(false);
		}
	}

	//Death animation
	if (health <= 0)
	{
		unsigned int explodeTexture = (gd)->EnemyShipExplodeTexture;
		if (alienType == 1) explodeTexture = (gd)->EnemyShipExplodeTexture;
		else if (alienType == 2) explodeTexture = (gd)->EnemyShipExplodeTexture2;
		else if (alienType == 3) explodeTexture = (gd)->EnemyShipExplodeTexture3;

		SetTexture(explodeTexture, 4);
		SetTextureSettings(120.0f, 120.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame)
		{
			int chance;
			if (alienType == 1) (gd)->SpaceInvadersPoints += 1000, chance = Randint(1, 32); //12.5% chance of anything dropping
			else if (alienType == 2) (gd)->SpaceInvadersPoints += 1250, chance = Randint(1, 24); //16.6% chance of anything dropping
			else if (alienType == 3) (gd)->SpaceInvadersPoints += 1500, chance = Randint(1, 16); //25% chance of anything dropping

			//Powerup drops
			if (chance == 1)
			{
				Powerup newPowerup(1, (gd)->SpeedUpTexture, 14, Vector2(position.x, position.y), 200, 0, Vector2(0, -1));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 2)
			{
				Powerup newPowerup(2, (gd)->HealUpTexture, 14, Vector2(position.x, position.y), 200, 0, Vector2(0, -1));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 3)
			{
				Powerup newPowerup(3, (gd)->LifeUpTexture, 14, Vector2(position.x, position.y), 200, 0, Vector2(0, -1));
				newPowerup.SetFrameRate(0.1f);
				newPowerup.SetCollider(20, 20);
				(gd)->Powerups.push_back(newPowerup); //Adds to list
			}
			else if (chance == 4)
			{
				Powerup newPowerup(4, (gd)->FireRateUpTexture, 14, Vector2(position.x, position.y), 200, 0, Vector2(0, -1));
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
		Shoot(gd);
	}

	if (isInvincible == true)
	{
		//Invincibility duration
		invincibilityTimer += getDeltaTime();
		if (invincibilityTimer > invincibilityDuration)
		{
			isInvincible = false;
			invincibilityTimer = 0;
		}

		//Flash duration
		flashTimer += getDeltaTime();
		if (flashTimer > flashDuration)
		{
			flash = true;
			flashTimer = 0;
		}

		if (flash == true)
		{
			Animate();
			flashTimer = 0;
			flash = false;
		}
	}
	else
	{
		Animate();
	}
}

void Alien::ResetAll()
{
}

template<typename T>
bool Alien::CollisionCheck(T & other)
{
	double radians = (textureAngle * (PI / 180));
	double degrees = (180 * radians / PI);
	float colliderAngle;
	if (ReverseRotation == false) colliderAngle = (float)fmod(degrees, 180);
	else colliderAngle = (float)(180 + fmod(degrees, 180));

	//Gets enemy collider vertex
	float otherTop = other.GetPosition().y + other.GetCollider().height / 2;
	float otherBottom = other.GetPosition().y - other.GetCollider().height / 2;
	float otherRight = other.GetPosition().x + other.GetCollider().width / 2;
	float otherLeft = other.GetPosition().x - other.GetCollider().width / 2;

	//Gets Alien collider vertex (Position depends on the angle)
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
