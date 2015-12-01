#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

NormalSprite::NormalSprite()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);

}

NormalSprite::NormalSprite(int newScreenID, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newHeight, float newWidth, float newAngle)
{
	ScreenID = newScreenID;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
}

NormalSprite::~NormalSprite()
{
}

int NormalSprite::GetScreenID()
{
	return ScreenID;
}

void NormalSprite::ResetAll()
{
}
