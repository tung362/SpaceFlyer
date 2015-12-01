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

NormalText::NormalText()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);

}

NormalText::NormalText(int newScreenID, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle)
{
	ScreenID = newScreenID;
	theTexture = newHandle;
	text = newText;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
}

NormalText::~NormalText()
{
}

int NormalText::GetScreenID()
{
	return ScreenID;
}

void NormalText::Animate()
{
	drawString(theTexture, text, position.x, position.y, textureWidth, textureHeight, textureAngle);
}

void NormalText::ResetAll()
{
}
