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
using std::cin;
using std::cout;
using std::endl;

Player::Player()
{
	position = Vector2(600 , 40);
	SetTextureSettings(80.0f, 80.0f, 90, true);
	speed = 400;
	shootTimer = 0;
	fireSpeed = 0.3f;
	debugSinglePress = true;
	health = 3; //3
	maxHealth = health;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

Player::Player(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(80.0f, 80.0f, 90, true);
	speed = newSpeed;
	rotationSpeed = 0;
	ReverseRotation = false;
	fireSpeed = 0.3f;
	debugSinglePress = true;
	health = 3; //3
	maxHealth = health;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

Player::~Player()
{
}

void Player::GetPlayerName(char * theName) //Needs a new char array to output to
{
	for (int i = 0; i < 128; ++i) 
	{
		theName[i] = playerName[i];
	}
}

void Player::SetPlayerName(const char * newName)
{
	for (unsigned int i = 0; i < strlen(newName); ++i)
	{
		playerName[i] = newName[i];
	}
}

float Player::GetMaxHealth()
{
	return maxHealth;
}

void Player::SetMaxHealth(float newMaxHealth)
{
	maxHealth = newMaxHealth;
}

float Player::GetInvincibilityDuration()
{
	return invincibilityDuration;
}

void Player::SetInvincibilityDuration(float newInvincibilityDuration)
{
	invincibilityDuration = newInvincibilityDuration;
}

bool Player::GetIsInvincible()
{
	return isInvincible;
}

void Player::SetIsInvincible(bool newIsInvincible)
{
	isInvincible = newIsInvincible;
}

int Player::GetBulletsShotCount(GlobalData* gd)
{
	return (gd)->SpaceInvadersShotsCount;
}

void Player::SetBulletShotCount(GlobalData* gd, int newCount)
{
	(gd)->SpaceInvadersShotsCount = newCount;
}

void Player::Movement(GlobalData* gd)
{
	Vector2 movement = Vector2(0, 0);

	//Gets the direction of movement and limit how far the player can move
	if (getKey(Keycode_A) == true && position.x - (textureWidth / 2) > 0) movement.x = -1;
	if (getKey(Keycode_D) == true && position.x + (textureWidth / 2) < 1200) movement.x = 1;

	//Pause Menu
	if (getKey(Keycode_ESCAPE) == true) (gd)->CurrentGameLevel = SIPause;

	//Apply movement
	position += (movement * speed) * getDeltaTime();
}

void Player::Shoot(GlobalData* gd)
{
	shootTimer += getDeltaTime();

	if(shootTimer >= fireSpeed && getKey(Keycode_SPACE) == true)
	{
		//Spawn bullet
		PlayerBullet newProjectile((gd)->PlayerBulletTexture, 1, Vector2(position.x + 3, position.y + 20), 1000, 90, Vector2(0, 1));
		newProjectile.SetCollider(10, 10);
		(gd)->PlayerBullets.push_back(newProjectile); //Adds to list
		(gd)->SpaceInvadersShotsCount += 1;

		//EnemyBullet newProjectile3((gd)->EnemyBulletTexture, 1, Vector2(position.x + 3, position.y + 400), 400, -90, Vector2(0, -1));
		//newProjectile3.SetCollider(10, 10);
		//(gd)->EnemyBullets.push_back(newProjectile3); //Adds to list

		shootTimer = 0;
	}
}

void Player::OnUpdateLogic(GlobalData* gd)
{
	//Debug Toggle
	if (getKey(Keycode_HOME) == true)
	{
		if (debugSinglePress == true) //Single click
		{
			if ((gd)->DebugMode == false) (gd)->DebugMode = true;
			else (gd)->DebugMode = false;
			debugSinglePress = false;
		}
	}
	else debugSinglePress = true;

	//Displays collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x - collider.width / 2, position.y, position.x + collider.width / 2, position.y);
		drawLine(position.x, position.y + collider.height / 2, position.x, position.y - collider.height / 2);
	}

	//Collision check
	for (unsigned int i = 0; i < (gd)->EnemyBullets.size(); ++i)
	{
		if (CollisionCheck<EnemyBullet>((gd)->EnemyBullets[i]) == true && (gd)->EnemyBullets[i].GetCanDamage() == true)
		{
			if (isInvincible == false)
			{
				health -= 1;
				isInvincible = true;
			}
			(gd)->EnemyBullets[i].SetCanDamage(false);
		}
	}

	for (unsigned int i = 0; i < (gd)->Powerups.size(); ++i)
	{
		if (CollisionCheck<Powerup>((gd)->Powerups[i]) == true && (gd)->Powerups[i].GetCanDamage() == true)
		{
			if ((gd)->Powerups[i].GetPowerupType() == 1) speed += 10; //Speed up
			else if ((gd)->Powerups[i].GetPowerupType() == 2) health = maxHealth; //Heal
			else if ((gd)->Powerups[i].GetPowerupType() == 3)
			{
				maxHealth += 1;
				health += 1; //Heal
			}
			else if ((gd)->Powerups[i].GetPowerupType() == 4) fireSpeed -= 0.05f;
			(gd)->Powerups[i].SetCanDamage(false);
		}
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

void Player::ResetAll()
{
}

template<typename T>
bool Player::CollisionCheck(T & other)
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

	//Gets Player collider vertex (Position depends on the angle)
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
