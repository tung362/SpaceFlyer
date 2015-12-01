#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "KeyCodeInput.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>
#include <fstream>
#include <string>

using namespace sfw;

HighScoreDisplay::HighScoreDisplay()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);
}

HighScoreDisplay::HighScoreDisplay(int newScreenID, unsigned newHandle, Vector2 newPosition, float newWidth, float newHeight, float newAngle)
{
	ScreenID = newScreenID;
	theTexture = newHandle;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	text = "";
}

HighScoreDisplay::~HighScoreDisplay()
{
}

int HighScoreDisplay::GetScreenID()
{
	return ScreenID;
}

std::string HighScoreDisplay::GetText()
{
	return text;
}

void HighScoreDisplay::OnUpdateLogic(GlobalData * gd)
{
	std::ifstream HighScoreFile;
	HighScoreFile.open("HighScores.txt", std::ios_base::in);

	std::string nameText;
	std::string pointsText;
	int points;
	std::string wavesText;
	int waves;
	std::string ShotText;
	std::string CountText;
	int shotCounts;

	int Highest = -1;

	if (HighScoreFile.is_open())
	{
		while (HighScoreFile >> nameText >> pointsText >> points >> wavesText >> waves >> ShotText >> CountText >> shotCounts)
		{
			if (Highest < points)
			{
				Highest = points;
				text = nameText + " " + pointsText + " " + std::to_string(points) + " " + wavesText + " " + std::to_string(waves) + " " + ShotText + " " + CountText + " " + std::to_string(shotCounts);
			}
		}
		HighScoreFile.close();
	}

	Animate();
}

void HighScoreDisplay::Animate()
{
	drawString(theTexture, text.c_str(), position.x, position.y, textureWidth, textureHeight, textureAngle);
}

void HighScoreDisplay::ResetAll()
{
}
