#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GlobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

void Mode2PauseUpdate(GlobalData* gd)
{
	for (unsigned int i = 0; i < (gd)->Cursors.size(); ++i)
		if ((gd)->Cursors[i].GetScreenID() == 4) (gd)->Cursors[i].OnUpdateLogic(gd);

	for (unsigned int i = 0; i < (gd)->Buttons.size(); ++i)
		if ((gd)->Buttons[i].GetScreenID() == 4) (gd)->Buttons[i].OnUpdateLogic(gd);
}