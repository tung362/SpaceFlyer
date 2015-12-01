#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GlobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;

void CreateMapMode2(GlobalData* gd)
{
	if ((gd)->CreateNewMapMode2 == true)
	{
		PlayerMode2 playerMode2((gd)->PlayerTexture, 1, Vector2(600, 400), 200, gd);
		playerMode2.SetCollider(60, 30);
		(gd)->PlayerMode2s.push_back(playerMode2);

		//Enemy
		EnemySmallShip enemySmallShip((gd)->SmallEnemyTexture, 1, Vector2(-100, 400), 140, gd);
		enemySmallShip.SetCollider(40, 40);
		(gd)->EnemySmallShips.push_back(enemySmallShip);

		EnemySmallShip enemySmallShip2((gd)->SmallEnemyTexture, 1, Vector2(1300, 400), 140, gd);
		enemySmallShip2.SetCollider(40, 40);
		(gd)->EnemySmallShips.push_back(enemySmallShip2);

		(gd)->Mode2WaveCount = 1;
		(gd)->CreateNewMapMode2 = false;
	}
	else
	{
		if ((gd)->EnemySmallShips.size() <= 0 && (gd)->EnemyMediumShips.size() <= 0 && (gd)->EnemyLargeShips.size() <= 0)
		{
			for (int i = 0; i < (gd)->Mode2WaveCount; ++i)
			{
				Vector2 randomPos = Vector2(Randint(-150.0f, 1350.0f), Randint(-150.0f, 950.0f));

				//If randomPos is outside of screen
				if (randomPos.x < 0 || randomPos.x > 1200 && randomPos.y < 0 || randomPos.y > 800)
				{
					if ((gd)->Mode2WaveCount >= 0 && (gd)->Mode2WaveCount <= 3)
					{
						EnemySmallShip enemySmallShip((gd)->SmallEnemyTexture, 1, randomPos, 140, gd);
						enemySmallShip.SetCollider(40, 40);
						(gd)->EnemySmallShips.push_back(enemySmallShip);
					}
					else if ((gd)->Mode2WaveCount >= 4 && (gd)->Mode2WaveCount <= 7)
					{
						int chance = Randint(1, 2);

						if (chance == 1)
						{
							EnemySmallShip enemySmallShip((gd)->SmallEnemyTexture, 1, randomPos, 140, gd);
							enemySmallShip.SetCollider(40, 40);
							(gd)->EnemySmallShips.push_back(enemySmallShip);
						}
						else if (chance == 2)
						{
							EnemyMediumShip enemySmallShip((gd)->MediumEnemyTexture, 1, randomPos, 70, gd);
							enemySmallShip.SetCollider(60, 40);
							(gd)->EnemyMediumShips.push_back(enemySmallShip);
						}
					}
					else if ((gd)->Mode2WaveCount >= 8)
					{
						int chance = Randint(1, 3);

						if (chance == 1)
						{
							EnemySmallShip enemySmallShip((gd)->SmallEnemyTexture, 1, randomPos, 140, gd);
							enemySmallShip.SetCollider(40, 40);
							(gd)->EnemySmallShips.push_back(enemySmallShip);
						}
						else if (chance == 2)
						{
							EnemyMediumShip enemySmallShip((gd)->MediumEnemyTexture, 1, randomPos, 70, gd);
							enemySmallShip.SetCollider(60, 40);
							(gd)->EnemyMediumShips.push_back(enemySmallShip);
						}
						else if (chance == 3)
						{
							EnemyLargeShip enemySmallShip((gd)->LargeEnemyTexture, 1, randomPos, 70, gd);
							enemySmallShip.SetCollider(90, 40);
							(gd)->EnemyLargeShips.push_back(enemySmallShip);
						}
					}
				}
				else i -= 1;
			}
			(gd)->Mode2WaveCount += 1;
		}
	}
}