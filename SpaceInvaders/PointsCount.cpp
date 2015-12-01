#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>
#include <sstream>

using namespace sfw;

PointsCount::PointsCount()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);
	currentCount = 0;
	countTimer = 0;
	countType = 1;
}

PointsCount::PointsCount(int newScreenID, int newCountType, unsigned newHandle, Vector2 newPosition, float newWidth, float newHeight, float newAngle)
{
	ScreenID = newScreenID;
	countType = newCountType;
	theTexture = newHandle;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	currentCount = 0;
	countTimer = 0;
}

PointsCount::~PointsCount()
{
}

int PointsCount::GetScreenID()
{
	return ScreenID;
}

void PointsCount::OnUpdateLogic(GlobalData * gd)
{
	if (countType == 1)
	{
		if (currentCount < (gd)->SpaceInvadersPoints)
		{

			countTimer += getDeltaTime();
			if (countTimer > 0.05)
			{
				currentCount += 123;
				countTimer = 0;
			}
		}

		if (currentCount > (gd)->SpaceInvadersPoints) currentCount = (gd)->SpaceInvadersPoints; //Prevents from going over the max

		//Convert Points to String
		std::stringstream pointsToString;
		pointsToString << currentCount;
		std::string Pstr = pointsToString.str();

		text = Pstr.c_str();
		Animate();
	}
	else if (countType == 2)
	{
		//Convert Points to String
		std::stringstream wavesToString;
		wavesToString << (gd)->SpaceInvaderWaveCount;
		std::string Pstr = wavesToString.str();

		text = Pstr.c_str();
		Animate();
	}
	else if (countType == 3)
	{

	}
	else if (countType == 4)
	{
		//Convert Points to String
		std::stringstream wavesToString;
		wavesToString << (gd)->Mode2WaveCount;
		std::string Pstr = wavesToString.str();

		text = Pstr.c_str();
		Animate();
	}
}

void PointsCount::Animate()
{
	drawString(theTexture, text, position.x, position.y, textureWidth, textureHeight, textureAngle);
}

void PointsCount::ResetAll()
{
}
