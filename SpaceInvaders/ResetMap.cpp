#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GLobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

void ResetMap(GlobalData* gd, bool CreateText)
{
	//Records data to text file
	if (CreateText == true)
	{
		std::fstream HighScoreFile;
		HighScoreFile.open("HighScores.txt", std::fstream::app);
		if (HighScoreFile.is_open())
		{
			HighScoreFile << "Points: " << (gd)->SpaceInvadersPoints << " Wave: " << (gd)->SpaceInvaderWaveCount << " Shots Count: " << (gd)->SpaceInvadersShotsCount << endl;
			HighScoreFile.close();
		}
	}

	//Reset game object back to default values
	//Space Invaders
	for (unsigned int i = 0; i < (gd)->PlayerBullets.size(); ++i) (gd)->PlayerBullets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyBullets.size(); ++i) (gd)->EnemyBullets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->Powerups.size(); ++i) (gd)->Powerups.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->Bunkers.size(); ++i) (gd)->Bunkers.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->BunkerBits.size(); ++i) (gd)->BunkerBits.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->Aliens.size(); ++i) (gd)->Aliens.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->Players.size(); ++i) (gd)->Players.clear(); //Destroy
	//Mode 2
	for (unsigned int i = 0; i < (gd)->PlayerMode2s.size(); ++i) (gd)->PlayerMode2s.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemySmallShips.size(); ++i) (gd)->EnemySmallShips.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyMediumShips.size(); ++i) (gd)->EnemyMediumShips.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyLargeShips.size(); ++i) (gd)->EnemyLargeShips.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerBlasterTurrets.size(); ++i) (gd)->PlayerBlasterTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerMissileTurrets.size(); ++i) (gd)->PlayerMissileTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerBurstTurrets.size(); ++i) (gd)->PlayerBurstTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerAntiProjectileTurrets.size(); ++i) (gd)->PlayerAntiProjectileTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerBurstMissiles.size(); ++i) (gd)->PlayerBurstMissiles.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerBurstProjectiles.size(); ++i) (gd)->PlayerBurstProjectiles.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->PlayerMissiles.size(); ++i) (gd)->PlayerMissiles.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyBlasterTurrets.size(); ++i) (gd)->EnemyBlasterTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyMissileTurrets.size(); ++i) (gd)->EnemyMissileTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyProjectileTurrets.size(); ++i) (gd)->EnemyProjectileTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyAntiProjectileTurrets.size(); ++i) (gd)->EnemyAntiProjectileTurrets.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyMissiles.size(); ++i) (gd)->EnemyMissiles.clear(); //Destroy
	for (unsigned int i = 0; i < (gd)->EnemyProjectiles.size(); ++i) (gd)->EnemyProjectiles.clear(); //Destroy

	//Reset Global Data
	(gd)->CreateNewMap = true;
	(gd)->HasPickedName = false;
	(gd)->LoseGame = false;
	(gd)->WinGame = false;
	(gd)->AlienMove = false;
	(gd)->WinLoseTimer = 0;
	(gd)->SpaceInvadersPoints = 0;
	(gd)->SpaceInvadersShotsCount = 0;
	(gd)->SpaceInvaderWaveCount = 0;
	(gd)->Mode2WaveCount = 0;
	//Mode 2
	(gd)->CreateNewMapMode2 = true;
	(gd)->BlasterUpgrade = 1;
	(gd)->MissileUpgrade = 0;
	(gd)->BurstUpgrade = 0;
	(gd)->MaxBlasterUpgrade = 5;
	(gd)->MaxMissileUpgrade = 2;
	(gd)->MaxBurstUpgrade = 2;
}