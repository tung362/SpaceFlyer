#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "keycodeInput.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

Cursor::Cursor()
{
	ScreenID = 1;
	SetTextureSettings(20.0f, 40.0f, 0, true);
	debugSinglePress = true;
}

Cursor::Cursor(int newScreenID, unsigned newHandle, int amountOfFrames, float newHeight, float newWidth, float newAngle)
{
	ScreenID = newScreenID;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	debugSinglePress = true;
}

Cursor::~Cursor()
{
}

int Cursor::GetScreenID()
{
	return ScreenID;
}

void Cursor::OnUpdateLogic(GlobalData * gd)
{
	//Debug Toggle
	if (getKey(Keycode_HOME) == true)
	{
		if (debugSinglePress == true) //Single click
		{
			if ((gd)->DebugMode == false) (gd)->DebugMode = true;
			else (gd)->DebugMode = false;
			debugSinglePress = false;
		}
	}
	else debugSinglePress = true;

	//Displays collider
	if ((gd)->DebugMode == true)
	{
		drawLine(position.x - collider.width / 2, position.y, position.x + collider.width / 2, position.y);
		drawLine(position.x, position.y + collider.height / 2, position.x, position.y - collider.height / 2);
	}

	position = Vector2(getMouseX(), getMouseY()); //Always be at the mouse's position

	Animate();
}

ColliderBounds Cursor::GetCollider()
{
	return collider;
}

void Cursor::SetCollider(float newWidth, float newHeight)
{
	collider = { newWidth , newHeight };
}

void Cursor::ResetAll()
{
}
