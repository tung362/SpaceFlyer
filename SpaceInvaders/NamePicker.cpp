#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "KeyCodeInput.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;

NamePicker::NamePicker()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);
	singlePress = true;
}

NamePicker::NamePicker(int newScreenID, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle)
{
	ScreenID = newScreenID;
	theTexture = newHandle;
	text = newText;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	singlePress = true;
}

NamePicker::~NamePicker()
{
}

int NamePicker::GetScreenID()
{
	return ScreenID;
}

std::string NamePicker::GetText()
{
	return text;
}

void NamePicker::OnUpdateLogic(GlobalData * gd)
{
	std::fstream HighScoreFile;

	//Add a letter
	if (getKey(Keycode_A) || getKey(Keycode_B) || getKey(Keycode_C) || getKey(Keycode_D) || getKey(Keycode_E) || getKey(Keycode_F) ||
		getKey(Keycode_G) || getKey(Keycode_H) || getKey(Keycode_I) || getKey(Keycode_J) || getKey(Keycode_K) || getKey(Keycode_L) ||
		getKey(Keycode_M) || getKey(Keycode_N) || getKey(Keycode_O) || getKey(Keycode_P) || getKey(Keycode_Q) || getKey(Keycode_R) ||
		getKey(Keycode_S) || getKey(Keycode_T) || getKey(Keycode_U) || getKey(Keycode_V) || getKey(Keycode_W) || getKey(Keycode_X) ||
		getKey(Keycode_Y) || getKey(Keycode_Z) || getKey(Keycode_1) || getKey(Keycode_2) || getKey(Keycode_3) || getKey(Keycode_4) ||
		getKey(Keycode_5) || getKey(Keycode_6) || getKey(Keycode_7) || getKey(Keycode_8) || getKey(Keycode_9) || getKey(Keycode_0) ||
		getKey(Keycode_SPACE))
	{
		//Single click
		if (singlePress == true) text += GetkeyPressed(), singlePress = false;
	}
	//Remove a letter
	else if (getKey(Keycode_BACKSPACE))
	{
		//Single click
		if (singlePress == true) text = text.substr(0, text.size() - 1), singlePress = false;
	}
	//Save to text file and move on
	else if (getKey(Keycode_ENTER))
	{
		//Single click
		if (singlePress == true)
		{
			//Create a name to put into the high score and player
			HighScoreFile.open("HighScores.txt", std::fstream::app);
			if (HighScoreFile.is_open())
			{
				HighScoreFile << text.c_str() << ": ";
				HighScoreFile.close();
			}
			(gd)->Players[0].SetPlayerName(text.c_str());

			(gd)->HasPickedName = true;
			singlePress = false;
		}
	}
	else singlePress = true;

	Animate();
}

void NamePicker::Animate()
{
	drawString(theTexture, text.c_str(), position.x, position.y, textureWidth, textureHeight, textureAngle);
}

void NamePicker::ResetAll()
{
}
