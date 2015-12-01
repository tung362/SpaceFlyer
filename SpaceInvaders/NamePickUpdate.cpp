#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GlobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;

void NamePickUpdate(GlobalData* gd)
{
	//General
	//Normal Sprites
	for (unsigned int i = 0; i < (gd)->NormalSprites.size(); ++i)
		if ((gd)->NormalSprites[i].GetScreenID() == 20) (gd)->NormalSprites[i].OnUpdateLogic(gd);
	//Normal Texts
	for (unsigned int i = 0; i < (gd)->NormalTexts.size(); ++i)
		if ((gd)->NormalTexts[i].GetScreenID() == 20) (gd)->NormalTexts[i].OnUpdateLogic(gd);
	//Name Picker
	for (unsigned int i = 0; i < (gd)->NamePickers.size(); ++i)
		if ((gd)->NamePickers[i].GetScreenID() == 20) (gd)->NamePickers[i].OnUpdateLogic(gd);
}