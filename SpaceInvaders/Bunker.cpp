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

Bunker::Bunker()
{
	position = Vector2(600, 40);
	SetTextureSettings(90.0f, 90.0f, 0, true);
	rotationSpeed = 0.2f;
	destroyed = false;

	//Randomly rotate left or right
	if(Randint(1, 2) == 1) ReverseRotation = false;
	else ReverseRotation = true;

	health = 5;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

Bunker::Bunker(unsigned newHandle, int amountOfFrames, Vector2 newPosition)
{
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(90.0f, 90.0f, 0, true);
	rotationSpeed = 0.2f;
	destroyed = false;

	//Randomly rotate left or right
	if (Randint(1, 2) == 1) ReverseRotation = false;
	else ReverseRotation = true;

	health = 5;
	invincibilityTimer = 0;
	invincibilityDuration = 1.3f;
	isInvincible = false;
	flashTimer = 0;
	flashDuration = 0.3f;
	flash = false;
}

Bunker::~Bunker()
{
}

void Bunker::Destroy()
{
	destroyed = true;
}

bool Bunker::isDestroyed()
{
	return destroyed;
}

float Bunker::GetInvincibilityDuration()
{
	return invincibilityDuration;
}

void Bunker::SetInvincibilityDuration(float newInvincibilityDuration)
{
	invincibilityDuration = newInvincibilityDuration;
}

bool Bunker::GetIsInvincible()
{
	return isInvincible;
}

void Bunker::SetIsInvincible(bool newIsInvincible)
{
	isInvincible = newIsInvincible;
}

void Bunker::Movement(GlobalData * gd)
{
	//if (180 * (textureAngle * (PI / 180)) / PI > 360) textureAngle = 0; //Reset to 0 degrees
	//else if (180 * (textureAngle * (PI / 180)) / PI < 0) textureAngle = 360; //go to 360 degrees
	if (ReverseRotation == false) textureAngle += rotationSpeed;
	else textureAngle -= rotationSpeed;

	/*if (getKey(Keycode_1) == true) textureAngle = 0;
	if (getKey(Keycode_2) == true) textureAngle = 90;
	if (getKey(Keycode_3) == true) textureAngle = 180;
	if (getKey(Keycode_4) == true) textureAngle = 270;
	if (getKey(Keycode_5) == true) textureAngle = 360;
	if (getKey(Keycode_MINUS) == true) textureAngle = textureAngle += rotationSpeed;
	if (getKey(Keycode_EQUAL) == true) textureAngle = textureAngle -= rotationSpeed;*/
}

void Bunker::OnUpdateLogic(GlobalData* gd)
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
		SetTextureSettings(170.0f, 170.0f, 0, true);
		SetFrameRate(0.07f);
		if (currentFrame == maxFrame)
		{
			Destroy();

			//Spawns tiny pieces
			BunkerBits bunkerBits1((gd)->Rock1Texture, 1, position, Vector2(Randint(-1.0f, 1.0f), Randint(-1.0f, 1.0f)));
			bunkerBits1.SetCollider(40, 40);
			(gd)->BunkerBits.push_back(bunkerBits1);

			BunkerBits bunkerBits2((gd)->Rock1Texture, 1, position, Vector2(Randint(-1.0f, 1.0f), Randint(-1.0f, 1.0f)));
			bunkerBits2.SetCollider(40, 40);
			(gd)->BunkerBits.push_back(bunkerBits2);

			BunkerBits bunkerBits3((gd)->Rock1Texture, 1, position, Vector2(Randint(-1.0f, 1.0f), Randint(-1.0f, 1.0f)));
			bunkerBits3.SetCollider(40, 40);
			(gd)->BunkerBits.push_back(bunkerBits3);
		}
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

void Bunker::ResetAll()
{
}

template<typename T>
bool Bunker::CollisionCheck(T & other)
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

	//Gets bunker collider vertex (Position depends on the angle)
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
