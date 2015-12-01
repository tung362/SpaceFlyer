#pragma once
#include "Sprite.h"
#include "Vector2.h"
#include "GameStruct.h"

struct GlobalData;

class EntityMode2 : public Sprite
{
protected:
	float speed;
	float rotationSpeed;
	bool ReverseRotation;
	Vector2 colliderOffset;
	ColliderBounds collider;
	float health;
	Vector2 forwardOrientation; //Original forward
	Vector2 rightSideOrientation; //Original right
	Vector2 leftSideOrientation; //Original left
	Vector2 forwardDirection; //Depends on orientation and angle
	Vector2 rightSideDirection; //Depends on orientation and angle
	Vector2 leftSideDirection; //Depends on orientation and angle
public:
	EntityMode2();
	~EntityMode2();
	float GetSpeed();
	void SetSpeed(float newSpeed);
	float GetRotationSpeed();
	void SetRotationSpeed(float newRotationSpeed);
	bool GetReverseRotation();
	void SetReverseRotation(bool newReverseRotation);
	float GetHealth();
	void SetHealth(float newHealth);
	virtual void CalculateDirection(GlobalData* gd); //Updates forwardDirection, rightSideDirection, and leftSideDirection depending on angle
	void OnUpdateLogic(GlobalData* gd);
	virtual void Movement(GlobalData* gd);
	ColliderBounds GetCollider();
	void SetColliderOffset(Vector2 newOffset);
	Vector2 GetColliderOffset();
	void SetCollider(float newWidth, float newHeight);
	Vector2 GetForwardOrientation();
	void SetForwardOrientation(Vector2 newDirection);
	Vector2 GetRightSideOrientation();
	void SetRightSideOrientation(Vector2 newDirection);
	Vector2 GetLeftSideOrientation();
	void SetLeftSideOrientation(Vector2 newDirection);
	Vector2 GetForwardDirection();
	Vector2 GetRightSideDirection();
	Vector2 GetLeftSideDirection();
};
