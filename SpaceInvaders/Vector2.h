#pragma once

class Vector2
{
public:
	float x;
	float y;
	Vector2();
	~Vector2();
	Vector2(float x1, float y1);
	void operator=(Vector2 otherVec);
	Vector2 operator+(Vector2 otherVec);
	Vector2 operator-(Vector2 otherVec);
	Vector2 operator*(Vector2 otherVec);
	Vector2 operator/(Vector2 otherVec);
	Vector2 operator*(float otherNum);
	Vector2 operator/(float otherNum);
	void operator+=(Vector2 otherVec);
	void operator-=(Vector2 otherVec);
	void operator*=(Vector2 otherVec);
	void operator/=(Vector2 otherVec);
	bool operator==(Vector2 otherVec);
	bool operator!=(Vector2 otherVec);
};
