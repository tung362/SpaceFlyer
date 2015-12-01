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

void CreateMap(GlobalData* gd)
{
	std::fstream HighScoreFile;

	if ((gd)->CreateNewMap == true)
	{
		//Game objects
		//Starting player
		Player player((gd)->PlayerTexture, 1, Vector2(600, 40), 400);
		player.SetCollider(40, 40);
		(gd)->Players.push_back(player);

		//Starting alien
		float alienStartingX = 50;
		for (int x = 0; x < 19; ++x)
		{
			Alien alien((gd)->SmallEnemyTexture, 1, Vector2(alienStartingX, 700), 30, 1);
			alien.SetCollider(40, 40);
			(gd)->Aliens.push_back(alien);
			alienStartingX = alienStartingX + 60;
		}
		(gd)->SpaceInvaderWaveCount += 1;

		//Starting bunker
		float bunkerStartingX = Randint(150.0f, 300.0f); //Random start spawn position
		for (int x = 0; x < 3; ++x)
		{
			Bunker bunker((gd)->Rock1Texture, 1, Vector2(bunkerStartingX, 150 + Randint(-10.0f, 90.0f)));
			bunker.SetCollider(80, 80);
			(gd)->Bunkers.push_back(bunker);
			bunkerStartingX = bunkerStartingX + Randint(300.0f, 400.0f);
		}

		(gd)->CreateNewMap = false;
	}
	else
	{
		//If no more aliens exists spawn new ones depending on wave count
		if ((gd)->Aliens.size() <= 0)
		{
			float alienStartingX = 50;
			int Type1Chance = 50 + (5 * (gd)->SpaceInvaderWaveCount); //150
			int Type2Chance = 25 + (10 * (gd)->SpaceInvaderWaveCount); //225
			int Type3Chance = 10 + (15 * (gd)->SpaceInvaderWaveCount); //310
			unsigned int theTexture = (gd)->SmallEnemyTexture;
			for (int x = 0; x < 19; ++x)
			{
				int chance = Randint(1 , Type1Chance + Type2Chance + Type3Chance);
				int theType = 1;
				if (chance >= 1 && chance <= Type1Chance) theType = 1, theTexture = (gd)->SmallEnemyTexture;
				if (chance > Type1Chance && chance <= Type2Chance) theType = 2, theTexture = (gd)->SmallEnemyTexture2;
				if (chance > Type2Chance && chance <= Type3Chance) theType = 3, theTexture = (gd)->SmallEnemyTexture3;

				Alien alien(theTexture, 1, Vector2(alienStartingX, 780), 30, theType);
				alien.SetCollider(40, 40);
				(gd)->Aliens.push_back(alien);

				float alienStartingY = alien.GetPosition().y + 60;
				for (int y = 0; y < (gd)->SpaceInvaderWaveCount; ++y)
				{
					int chance2 = Randint(1, Type1Chance + Type2Chance + Type3Chance);
					int theType2 = 1;
					if (chance2 >= 1 && chance2 <= Type1Chance) theType2 = 1, theTexture = (gd)->SmallEnemyTexture;
					if (chance2 > Type1Chance && chance2 <= Type2Chance) theType2 = 2, theTexture = (gd)->SmallEnemyTexture2;
					if (chance2 > Type2Chance && chance2 <= Type3Chance) theType2 = 3, theTexture = (gd)->SmallEnemyTexture3;

					Alien alien2(theTexture, 1, Vector2(alienStartingX, alienStartingY), 30, theType2);
					alien2.SetCollider(40, 40);
					(gd)->Aliens.push_back(alien2);
					alienStartingY = alienStartingY + 60;
				}
				alienStartingX = alienStartingX + 60;
			}
			(gd)->SpaceInvaderWaveCount += 1;
		}
	}
}