#include "Entity.h"
#include "GameFunction.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

Entity::Entity()
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
}


Entity::~Entity()
{
}

float Entity::GetSpeed()
{
	return speed;
}

void Entity::SetSpeed(float newSpeed)
{
	speed = newSpeed;
}

float Entity::GetRotationSpeed()
{
	return rotationSpeed;
}

void Entity::SetRotationSpeed(float newRotationSpeed)
{
	rotationSpeed = newRotationSpeed;
}

bool Entity::GetReverseRotation()
{
	return ReverseRotation;
}

void Entity::SetReverseRotation(bool newReverseRotation)
{
	ReverseRotation = newReverseRotation;
}

float Entity::GetHealth()
{
	return health;
}

void Entity::SetHealth(float newHealth)
{
	health = newHealth;
}

void Entity::OnUpdateLogic(GlobalData* gd)
{
	Movement(gd);
	Animate();
}

void Entity::Movement(GlobalData* gd)
{
}

ColliderBounds Entity::GetCollider()
{
	return collider;
}

void Entity::SetColliderOffset(Vector2 newOffset)
{
	colliderOffset = newOffset;
}

Vector2 Entity::GetColliderOffset()
{
	return colliderOffset;
}

void Entity::SetCollider(float newWidth, float newHeight)
{
	collider = { newWidth , newHeight };
}
