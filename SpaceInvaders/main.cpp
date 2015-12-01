#include <iostream>
#include <cstring>
#include "sfwdraw.h"
#include "GameObject.h"
#include "GameFunction.h"
#include "Entity.h"
#include "Vector2.h"
#include "GLobalData.h"
#include <ctime>
#include <fstream>
#include <vector>

using namespace sfw;

int main()
{
	//Screen Size
	initContext(1200, 800, "Space Invader");
	setBackgroundColor(BLACK);
	srand(time(NULL));

	//Used by all game objects, keeps track of points, etc etc
	GlobalData globalData;
	CreateDefaultGlobalData(&globalData);

	float AlienMoveTimer = 0;

	//OnLogicUpdate
	while (stepContext())
	{
		CreateNonLevelObjects(&globalData); //Creates menu buttons and texts

		switch (globalData.CurrentGameLevel)
		{
		case Exit:
			break;
		case SplashScreen:
			SplashScreenState(&globalData);
			break;
		case MainMenu:
			MainMenuState(&globalData);
			break;
		case Instruction:
			InstructionState(&globalData);
			break;
		case Instruction2:
			Instruction2State(&globalData);
			break;
		case About:
			AboutState(&globalData);
			break;
		case HighScore:
			HighScoreState(&globalData);
			break;

		//Start of mode 1
		case SIStartGame:
			CreateMap(&globalData);
		case SINamePick:
			if (globalData.HasPickedName == false)
			{
				NamePickUpdate(&globalData);
				break;
			}
		case Mode1:
			if (globalData.LoseGame == false && globalData.WinGame == false)
			{
				//Lets aliens move
				if (globalData.AlienMove == false)
				{
					AlienMoveTimer += getDeltaTime();
					if (AlienMoveTimer >= 0.8f - (0.07f * globalData.SpaceInvaderWaveCount))
					{
						globalData.AlienMove = true;
						AlienMoveTimer = 0;
					}
				}
				Mode1Update(&globalData);
			}
			else globalData.CurrentGameLevel = EndGame;
			break;
		case SIPause:
			Mode1PauseUpdate(&globalData);
			break;

		//Start of mode 2
		case M2StartGame:
			CreateMapMode2(&globalData);
		case Mode2:
			if (globalData.LoseGame == false && globalData.WinGame == false)
			{
				Mode2Update(&globalData);
			}
			else globalData.CurrentGameLevel = EndGameMode2;
			break;
		case M2Pause:
			Mode2PauseUpdate(&globalData);
			break;

		//End
		case EndGame:
			WinLose(&globalData, 10);
			break;
		case EndGameMode2:
			WinLose(&globalData, 11);
			break;
		default:
			break;
		}

		//Exits Console And Client
		if (globalData.CurrentGameLevel == Exit) break;
	}

	termContext();
	return 0;
}