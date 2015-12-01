#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>
#include <string>

using namespace sfw;

void SplashScreenState(GlobalData* gd)
{
	(gd)->SplashScreenTimer += getDeltaTime();

	//Go to main menu after a few seconds
	if ((gd)->SplashScreenTimer >= 5)
	{
		(gd)->CurrentGameLevel = MainMenu;
		(gd)->SplashScreenTimer = 0;
	}

	//Normal Sprites
	for (unsigned int i = 0; i < (gd)->NormalSprites.size(); ++i)
		if ((gd)->NormalSprites[i].GetScreenID() == 1) (gd)->NormalSprites[i].OnUpdateLogic(gd);
}