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

void Mode2Update(GlobalData* gd)
{
	//General
	//Mouse
	for (unsigned int i = 0; i < (gd)->Cursors.size(); ++i)
		if ((gd)->Cursors[i].GetScreenID() == 11) (gd)->Cursors[i].OnUpdateLogic(gd);
	//Normal Sprites
	for (unsigned int i = 0; i < (gd)->NormalSprites.size(); ++i)
		if ((gd)->NormalSprites[i].GetScreenID() == 11) (gd)->NormalSprites[i].OnUpdateLogic(gd);
	//Normal Texts
	for (unsigned int i = 0; i < (gd)->NormalTexts.size(); ++i)
		if ((gd)->NormalTexts[i].GetScreenID() == 11) (gd)->NormalTexts[i].OnUpdateLogic(gd);
	//Point Counts
	for (unsigned int i = 0; i < (gd)->PointsCounts.size(); ++i)
		if ((gd)->PointsCounts[i].GetScreenID() == 11) (gd)->PointsCounts[i].OnUpdateLogic(gd);
	//Health bars
	for (unsigned int i = 0; i < (gd)->HealthBars.size(); ++i)
		if ((gd)->HealthBars[i].GetScreenID() == 11) (gd)->HealthBars[i].OnUpdateLogic(gd);
	//Power up
	for (unsigned int i = 0; i < (gd)->Powerups.size(); ++i)
	{
		(gd)->Powerups[i].OnUpdateLogic(gd);
		if ((gd)->Powerups[i].isDestroyed() == true) (gd)->Powerups.erase((gd)->Powerups.begin() + i); //Destroy
	}

	//Player
	for (unsigned int i = 0; i < (gd)->PlayerMode2s.size(); ++i) (gd)->PlayerMode2s[i].OnUpdateLogic(gd);

	//Enemy
	//Enemy Small Ship
	for (unsigned int i = 0; i < (gd)->EnemySmallShips.size(); ++i)
	{
		(gd)->EnemySmallShips[i].OnUpdateLogic(gd);
		if ((gd)->EnemySmallShips[i].isDestroyed() == true) (gd)->EnemySmallShips.erase((gd)->EnemySmallShips.begin() + i);
	}
	//Enemy Medium Ship
	for (unsigned int i = 0; i < (gd)->EnemyMediumShips.size(); ++i)
	{
		(gd)->EnemyMediumShips[i].OnUpdateLogic(gd);
		if ((gd)->EnemyMediumShips[i].isDestroyed() == true) (gd)->EnemyMediumShips.erase((gd)->EnemyMediumShips.begin() + i);
	}
	//Enemy Large Ship
	for (unsigned int i = 0; i < (gd)->EnemyLargeShips.size(); ++i)
	{
		(gd)->EnemyLargeShips[i].OnUpdateLogic(gd);
		if ((gd)->EnemyLargeShips[i].isDestroyed() == true) (gd)->EnemyLargeShips.erase((gd)->EnemyLargeShips.begin() + i);
	}

	//Player
	//Player Blaster Turret
	for (unsigned int i = 0; i < (gd)->PlayerBlasterTurrets.size(); ++i) (gd)->PlayerBlasterTurrets[i].OnUpdateLogic(gd);
	//Player Missile Turret
	for (unsigned int i = 0; i < (gd)->PlayerMissileTurrets.size(); ++i) (gd)->PlayerMissileTurrets[i].OnUpdateLogic(gd);
	//Player Burst Turret
	for (unsigned int i = 0; i < (gd)->PlayerBurstTurrets.size(); ++i) (gd)->PlayerBurstTurrets[i].OnUpdateLogic(gd);
	//Player Anti Projectile Turret
	for (unsigned int i = 0; i < (gd)->PlayerAntiProjectileTurrets.size(); ++i) (gd)->PlayerAntiProjectileTurrets[i].OnUpdateLogic(gd);
	

	//Enemy
	//Enemy Blaster Turret
	for (unsigned int i = 0; i < (gd)->EnemyBlasterTurrets.size(); ++i) (gd)->EnemyBlasterTurrets[i].OnUpdateLogic(gd);
	//Enemy Missile Turret
	for (unsigned int i = 0; i < (gd)->EnemyMissileTurrets.size(); ++i) (gd)->EnemyMissileTurrets[i].OnUpdateLogic(gd);
	//Enemy Projectile Turret
	for (unsigned int i = 0; i < (gd)->EnemyProjectileTurrets.size(); ++i) (gd)->EnemyProjectileTurrets[i].OnUpdateLogic(gd);
	//Enemy Anti Projectile Turret
	for (unsigned int i = 0; i < (gd)->EnemyAntiProjectileTurrets.size(); ++i) (gd)->EnemyAntiProjectileTurrets[i].OnUpdateLogic(gd);

	//Player
	//Player bullet
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i)
	{
		(gd)->PlayerBullets[i].OnUpdateLogic(gd);
		if ((gd)->PlayerBullets[i].isDestroyed() == true) (gd)->PlayerBullets.erase((gd)->PlayerBullets.begin() + i); //Destroy
	}
	//Player Burst Missile
	for (unsigned int i = 0; i < (gd)->PlayerBurstMissiles.size(); ++i)
	{
		(gd)->PlayerBurstMissiles[i].OnUpdateLogic(gd);
		if ((gd)->PlayerBurstMissiles[i].isDestroyed() == true) (gd)->PlayerBurstMissiles.erase((gd)->PlayerBurstMissiles.begin() + i); //Destroy
	}
	//Player Burst Projectile
	for (unsigned int i = 0; i < (gd)->PlayerBurstProjectiles.size(); ++i)
	{
		(gd)->PlayerBurstProjectiles[i].OnUpdateLogic(gd);
		if ((gd)->PlayerBurstProjectiles[i].isDestroyed() == true) (gd)->PlayerBurstProjectiles.erase((gd)->PlayerBurstProjectiles.begin() + i); //Destroy
	}
	//Player Missile
	for (unsigned int i = 0; i < (gd)->PlayerMissiles.size(); ++i)
	{
		(gd)->PlayerMissiles[i].OnUpdateLogic(gd);
		if ((gd)->PlayerMissiles[i].isDestroyed() == true) (gd)->PlayerMissiles.erase((gd)->PlayerMissiles.begin() + i); //Destroy
	}

	//Enemy
	//Enemy bullet
	for (unsigned int i = 0; i < (gd)->EnemyBullets.size(); ++i)
	{
		(gd)->EnemyBullets[i].OnUpdateLogic(gd);
		if ((gd)->EnemyBullets[i].isDestroyed() == true) (gd)->EnemyBullets.erase((gd)->EnemyBullets.begin() + i); //Destroy
	}
	//Enemy Missile
	for (unsigned int i = 0; i < (gd)->EnemyMissiles.size(); ++i)
	{
		(gd)->EnemyMissiles[i].OnUpdateLogic(gd);
		if ((gd)->EnemyMissiles[i].isDestroyed() == true) (gd)->EnemyMissiles.erase((gd)->EnemyMissiles.begin() + i); //Destroy
	}
	//Enemy Projectile
	for (unsigned int i = 0; i < (gd)->EnemyProjectiles.size(); ++i)
	{
		(gd)->EnemyProjectiles[i].OnUpdateLogic(gd);
		if ((gd)->EnemyProjectiles[i].isDestroyed() == true) (gd)->EnemyProjectiles.erase((gd)->EnemyProjectiles.begin() + i); //Destroy
	}
}