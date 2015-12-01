#include "EntityMode2.h"
#include "GameFunction.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

EntityMode2::EntityMode2()
{
	position = Vector2(400, 400);
	speed = 0;
	health = 1;
	SetTextureSettings(1, 1, 0, true);
	startingFrame = 0;
	currentFrame = 0;
	maxFrame = 0;
	AnimationTimer = 0;
	frameRate = 0.1f;
	rotationSpeed = 0;
	ReverseRotation = false;
	collider = { 0, 0 };
	forwardOrientation = Vector2(1, 0);
	rightSideOrientation = Vector2(0, -1);
	leftSideOrientation = Vector2(0, 1);
	forwardDirection = Vector2(1, 0);
	rightSideDirection = Vector2(0, -1);
	leftSideDirection = Vector2(0, 1);
}


EntityMode2::~EntityMode2()
{
}

float EntityMode2::GetSpeed()
{
	return speed;
}

void EntityMode2::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float EntityMode2::GetRotationSpeed()
{
	return rotationSpeed;
}

void EntityMode2::SetRotationSpeed(float newRotationSpeed)
{
	rotationSpeed = newRotationSpeed;
}

bool EntityMode2::GetReverseRotation()
{
	return ReverseRotation;
}

void EntityMode2::SetReverseRotation(bool newReverseRotation)
{
	ReverseRotation = newReverseRotation;
}

float EntityMode2::GetHealth()
{
	return health;
}

void EntityMode2::SetHealth(float newHealth)
{
	health = newHealth;
}

void EntityMode2::CalculateDirection(GlobalData* gd)
{
	forwardDirection = RotatePoint(0, 0, textureAngle, Vector2(forwardOrientation.x, forwardOrientation.y));
	rightSideDirection = RotatePoint(0, 0, textureAngle, Vector2(rightSideOrientation.x, rightSideOrientation.y));
	leftSideDirection = RotatePoint(0, 0, textureAngle, Vector2(leftSideOrientation.x, leftSideOrientation.y));
}

void EntityMode2::OnUpdateLogic(GlobalData* gd)
{
	CalculateDirection(gd);
	Movement(gd);
	Animate();
}

void EntityMode2::Movement(GlobalData* gd)
{
}

ColliderBounds EntityMode2::GetCollider()
{
	return collider;
}

void EntityMode2::SetColliderOffset(Vector2 newOffset)
{
	colliderOffset = newOffset;
}

Vector2 EntityMode2::GetColliderOffset()
{
	return colliderOffset;
}

void EntityMode2::SetCollider(float newWidth, float newHeight)
{
	collider = { newWidth , newHeight };
}

Vector2 EntityMode2::GetForwardOrientation()
{
	return forwardOrientation;
}

void EntityMode2::SetForwardOrientation(Vector2 newDirection)
{
	forwardOrientation = newDirection;
}

Vector2 EntityMode2::GetRightSideOrientation()
{
	return rightSideOrientation;
}

void EntityMode2::SetRightSideOrientation(Vector2 newDirection)
{
	rightSideOrientation = newDirection;
}

Vector2 EntityMode2::GetLeftSideOrientation()
{
	return leftSideOrientation;
}

void EntityMode2::SetLeftSideOrientation(Vector2 newDirection)
{
	leftSideOrientation = newDirection;
}

Vector2 EntityMode2::GetForwardDirection()
{
	return forwardDirection;
}

Vector2 EntityMode2::GetRightSideDirection()
{
	return rightSideDirection;
}

Vector2 EntityMode2::GetLeftSideDirection()
{
	return leftSideDirection;
}
