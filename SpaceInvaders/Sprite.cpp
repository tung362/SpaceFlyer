#include "Sprite.h"
#include "GameFunction.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;

Sprite::Sprite()
{
	position = Vector2(0, 0);
	SetTextureSettings(1, 1, 0, true);
	startingFrame = 0;
	currentFrame = 0;
	maxFrame = 0;
	AnimationTimer = 0;
	frameRate = 1;
}

Sprite::~Sprite()
{
}

Vector2 Sprite::GetPosition()
{
	return position;
}

void Sprite::SetPosition(Vector2 newPosition)
{
	position = newPosition;
}

void Sprite::SetPosition(float x, float y)
{
	position = Vector2(x, y);
}

int Sprite::GetStartingFrame()
{
	return startingFrame;
}

void Sprite::SetStartingFrame(int newStartingFrame)
{
	startingFrame = newStartingFrame;
}

int Sprite::GetCurrentFrame()
{
	return currentFrame;
}

void Sprite::SetCurrentFrame(int newCurrentFrame)
{
	currentFrame = newCurrentFrame;
}

int Sprite::GetMaxFrame()
{
	return maxFrame;
}

void Sprite::SetMaxFrame(int newMaxFrame)
{
	maxFrame = newMaxFrame;
}

float Sprite::GetFrameRate()
{
	return frameRate;
}

void Sprite::SetFrameRate(float newFrameRate)
{
	frameRate = newFrameRate;
}

void Sprite::ResetFrame()
{
	currentFrame = startingFrame;
}

void Sprite::SetTextureSettings(float width, float height, float angle, bool centered)
{
	textureWidth = width;
	textureHeight = height;
	textureAngle = angle;
	textureCentered = centered;
}

void Sprite::SetTexture(unsigned newTexture)
{
	theTexture = newTexture;
	maxFrame = 0;
}

void Sprite::SetTexture(unsigned newTexture, int amountOfFrames)
{
	theTexture = newTexture;
	maxFrame = amountOfFrames - 1;
}

void Sprite::RenderTexture()
{
	drawTexture(theTexture, position.x, position.y, textureWidth, textureHeight, textureAngle, textureCentered);
}

void Sprite::Animate()
{
	if (maxFrame != 0)
	{
		AnimationTimer += getDeltaTime();

		if (AnimationTimer > frameRate) //Switches to next frame
		{
			currentFrame += 1;
			AnimationTimer = 0;
		}

		if (currentFrame > maxFrame) //loop back to starting
		{
			AnimationTimer = 0;
			ResetFrame();
		}

		drawTexture(theTexture, position.x, position.y, textureWidth, textureHeight, textureAngle, textureCentered, currentFrame);
	}
	else RenderTexture();
}

void Sprite::OnUpdateLogic(GlobalData* gd)
{
	Animate();
}

void Sprite::ResetAll()
{
}

