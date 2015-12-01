#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GLobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;

void WinLose(GlobalData* gd, int ScreenID)
{
	(gd)->WinLoseTimer += getDeltaTime();
	if ((gd)->LoseGame == true)
	{
		for (unsigned int i = 0; i < (gd)->NormalTexts.size(); ++i)
			if ((gd)->NormalTexts[i].GetScreenID() == 15) (gd)->NormalTexts[i].OnUpdateLogic(gd);
	}

	//After a few seconds reset all and go back to main menu
	if ((gd)->WinLoseTimer >= 5)
	{
		//If mode one, also record data to text file, else don't record data
		if (ScreenID == 10) ResetMap(gd, true);
		else ResetMap(gd, false);

		(gd)->CurrentGameLevel = MainMenu;
		(gd)->WinLoseTimer = 0;
	}
}