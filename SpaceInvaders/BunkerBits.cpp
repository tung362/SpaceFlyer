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

BunkerBits::BunkerBits()
{
	position = Vector2(600, 40);
	moveDirection = Vector2(0, 0);
	SetTextureSettings(45.0f, 45.0f, 0, true);
	rotationSpeed = 0.2f;
	speed = Randint(35.0f, 55.0f);
	destroyed = false;

	//Randomly rotate left or right
	if (Randint(1, 2) == 1) ReverseRotation = false;
	else ReverseRotation = true;

	health = 2;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

BunkerBits::BunkerBits(unsigned newHandle, int amountOfFrames, Vector2 newPosition, Vector2 newMoveDirection)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	moveDirection = newMoveDirection;
	SetTextureSettings(45.0f, 45.0f, 0, true);
	rotationSpeed = 0.2f;
	speed = Randint(35.0f, 55.0f);
	destroyed = false;

	//Randomly rotate left or right
	if (Randint(1, 2) == 1) ReverseRotation = false;
	else ReverseRotation = true;

	health = 2;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

BunkerBits::~BunkerBits()
{
}

void BunkerBits::Destroy()
{
	destroyed = true;
}

bool BunkerBits::isDestroyed()
{
	return destroyed;
}

float BunkerBits::GetInvincibilityDuration()
{
	return invincibilityDuration;
}

void BunkerBits::SetInvincibilityDuration(float newInvincibilityDuration)
{
	invincibilityDuration = newInvincibilityDuration;
}

bool BunkerBits::GetIsInvincible()
{
	return isInvincible;
}

void BunkerBits::SetIsInvincible(bool newIsInvincible)
{
	isInvincible = newIsInvincible;
}

void BunkerBits::Movement(GlobalData * gd)
{
	Vector2 movement = Vector2(0, 0);

	//Rotation
	if (ReverseRotation == false) textureAngle += rotationSpeed;
	else textureAngle -= rotationSpeed;

	//Movement
	if (speed >= 1 && position.y >= 130)
	{
		movement = moveDirection;
		position += (movement * speed) * getDeltaTime();
		speed -= 0.3f;
	}
}

void BunkerBits::OnUpdateLogic(GlobalData* gd)
{
	//Displays collider
	if ((gd)->DebugMode == true)
	{
		double radians = textureAngle * (PI / 180);
		double degrees = 180 * radians / PI;
		float colliderAngle;
		if (ReverseRotation == false) colliderAngle = (float)fmod(degrees, 180);
		else colliderAngle = (float)(180 + fmod(degrees, 180));

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
			if (isInvincible == false)
			{
				health -= 1;
				isInvincible = true;
			}
			(gd)->EnemyBullets[i].SetCanDamage(false);
		}
	}

	//Death animation
	if (health <= 0)
	{
		SetTexture((gd)->PlayerShipExplodeTexture, 4);
		SetTextureSettings(85.0f, 85.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame) Destroy();
	}
	else
	{
		Movement(gd);
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

void BunkerBits::ResetAll()
{
}

template<typename T>
bool BunkerBits::CollisionCheck(T & other)
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

	//Gets BunkerBits collider vertex (Position depends on the angle)
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
