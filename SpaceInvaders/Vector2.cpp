#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;

Vector2::Vector2()
{
	x = 0;
	y = 0;
}

Vector2::~Vector2()
{
}

Vector2::Vector2(float x1, float y1)
{
	x = x1;
	y = y1;
}

void Vector2::operator=(Vector2 otherVec)
{
	x = otherVec.x;
	y = otherVec.y;
}

Vector2 Vector2::operator+(Vector2 otherVec)
{
	Vector2 temp;
	temp.x = x + otherVec.x;
	temp.y = y + otherVec.y;
	return temp;
}

Vector2 Vector2::operator-(Vector2 otherVec)
{
	Vector2 temp;
	temp.x = x - otherVec.x;
	temp.y = y - otherVec.y;
	return temp;
}

Vector2 Vector2::operator*(Vector2 otherVec)
{
	Vector2 temp;
	temp.x = x * otherVec.x;
	temp.y = y * otherVec.y;
	return temp;
}

Vector2 Vector2::operator/(Vector2 otherVec)
{
	Vector2 temp;
	temp.x = x / otherVec.x;
	temp.y = y / otherVec.y;
	return temp;
}

Vector2 Vector2::operator*(float otherNum)
{
	Vector2 temp;
	temp.x = x * otherNum;
	temp.y = y * otherNum;
	return temp;
}

Vector2 Vector2::operator/(float otherNum)
{
	Vector2 temp;
	temp.x = x / otherNum;
	temp.y = y / otherNum;
	return temp;
}

void Vector2::operator+=(Vector2 otherVec)
{
	x += otherVec.x;
	y += otherVec.y;
}

void Vector2::operator-=(Vector2 otherVec)
{
	x -= otherVec.x;
	y -= otherVec.y;
}

void Vector2::operator*=(Vector2 otherVec)
{
	x *= otherVec.x;
	y *= otherVec.y;
}

void Vector2::operator/=(Vector2 otherVec)
{
	x /= otherVec.x;
	y /= otherVec.y;
}

bool Vector2::operator==(Vector2 otherVec)
{
	if (x == otherVec.x && y == otherVec.y) return true;
	else return false;
}

bool Vector2::operator!=(Vector2 otherVec)
{
	if (x != otherVec.x || y != otherVec.y) return true;
	else return false;
}
