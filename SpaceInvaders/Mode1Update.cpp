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

void Mode1Update(GlobalData* gd)
{
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		(gd)->PlayerBullets[i].OnUpdateLogic(gd);
		if ((gd)->PlayerBullets[i].isDestroyed() == true) (gd)->PlayerBullets.erase((gd)->PlayerBullets.begin() + i); //Destroy
	}

	for (unsigned int i = 0; i < (gd)->EnemyBullets.size(); ++i)
	{
		(gd)->EnemyBullets[i].OnUpdateLogic(gd);
		if ((gd)->EnemyBullets[i].isDestroyed() == true) (gd)->EnemyBullets.erase((gd)->EnemyBullets.begin() + i); //Destroy
	}

	for (unsigned int i = 0; i < (gd)->Powerups.size(); ++i)
	{
		(gd)->Powerups[i].OnUpdateLogic(gd);
		if ((gd)->Powerups[i].isDestroyed() == true) (gd)->Powerups.erase((gd)->Powerups.begin() + i); //Destroy
	}

	for (unsigned int i = 0; i < (gd)->Bunkers.size(); ++i)
	{
		(gd)->Bunkers[i].OnUpdateLogic(gd);
		if ((gd)->Bunkers[i].isDestroyed() == true) (gd)->Bunkers.erase((gd)->Bunkers.begin() + i);
	}

	for (unsigned int i = 0; i < (gd)->BunkerBits.size(); ++i)
	{
		(gd)->BunkerBits[i].OnUpdateLogic(gd);
		if ((gd)->BunkerBits[i].isDestroyed() == true) (gd)->BunkerBits.erase((gd)->BunkerBits.begin() + i);
	}

	for (unsigned int i = 0; i < (gd)->Aliens.size(); ++i)
	{
		(gd)->Aliens[i].OnUpdateLogic(gd);
		if ((gd)->Aliens[i].isDestroyed() == true) (gd)->Aliens.erase((gd)->Aliens.begin() + i);

		if (i == (gd)->Aliens.size() - 1) (gd)->AlienMove = false; //Stop Alien move
	}

	for (unsigned int i = 0; i < (gd)->Players.size(); ++i) (gd)->Players[i].OnUpdateLogic(gd);

	for (unsigned int i = 0; i < (gd)->NormalSprites.size(); ++i)
		if ((gd)->NormalSprites[i].GetScreenID() == 10) (gd)->NormalSprites[i].OnUpdateLogic(gd);

	for (unsigned int i = 0; i < (gd)->NormalTexts.size(); ++i)
		if ((gd)->NormalTexts[i].GetScreenID() == 10) (gd)->NormalTexts[i].OnUpdateLogic(gd);

	for (unsigned int i = 0; i < (gd)->HealthBars.size(); ++i)
		if ((gd)->HealthBars[i].GetScreenID() == 10) (gd)->HealthBars[i].OnUpdateLogic(gd);

	for (unsigned int i = 0; i < (gd)->PointsCounts.size(); ++i)
		if ((gd)->PointsCounts[i].GetScreenID() == 10) (gd)->PointsCounts[i].OnUpdateLogic(gd);
}