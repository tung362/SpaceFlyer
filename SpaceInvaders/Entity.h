#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "GameStruct.h"

struct GlobalData;

class Entity : public Sprite
{
protected:
	float speed;
	float rotationSpeed;
	bool ReverseRotation;
	Vector2 colliderOffset;
	ColliderBounds collider;
	float health;
public:
	Entity();
	~Entity();
	float GetSpeed();
	void SetSpeed(float newSpeed);
	float GetRotationSpeed();
	void SetRotationSpeed(float newRotationSpeed);
	bool GetReverseRotation();
	void SetReverseRotation(bool newReverseRotation);
	float GetHealth();
	void SetHealth(float newHealth);
	void OnUpdateLogic(GlobalData* gd);
	virtual void Movement(GlobalData* gd);
	ColliderBounds GetCollider();
	void SetColliderOffset(Vector2 newOffset);
	Vector2 GetColliderOffset();
	void SetCollider(float newWidth, float newHeight);
};
