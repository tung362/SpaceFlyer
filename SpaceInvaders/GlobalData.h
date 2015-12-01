#pragma once
#include "GameObject.h"
#include "sfwdraw.h"
#include <vector>
using std::vector;

//Global Data
enum Level
{
	Exit, SplashScreen, MainMenu, Instruction, Instruction2, About, HighScore, SIStartGame, SINamePick, Mode1, SIPause, M2StartGame, Mode2, M2Pause, EndGame, EndGameMode2
};

struct GlobalData
{
	Level CurrentGameLevel;
	Level TempLevel;
	bool CreateNewMap;
	bool HasPickedName;
	bool CreateNonLevelObjects;
	bool LoseGame;
	bool WinGame;
	bool AlienMove; //When can the aliens move
	bool DebugMode;
	float WinLoseTimer;
	float SplashScreenTimer;
	//Mode 2
	bool CreateNewMapMode2;
	float BlasterUpgrade;
	float MissileUpgrade;
	float BurstUpgrade;
	float MaxBlasterUpgrade;
	float MaxMissileUpgrade;
	float MaxBurstUpgrade;

	//Space invaders game mode
	int SpaceInvadersPoints;
	int SpaceInvadersShotsCount;
	int SpaceInvaderWaveCount;

	//Mode 2 game mode
	int Mode2WaveCount;

	//Keeps track of multiple objects
	vector<NamePicker> NamePickers;
	vector<HighScoreDisplay> HighScoreDisplays;
	vector<Player> Players;
	vector<Alien> Aliens;
	vector<Bunker> Bunkers;
	vector<BunkerBits> BunkerBits;
	vector<PlayerBullet> PlayerBullets;
	vector<EnemyBullet> EnemyBullets;
	vector<Powerup> Powerups;
	//Mode 2
	vector<PlayerMode2> PlayerMode2s;
	vector<PlayerBlasterTurret> PlayerBlasterTurrets;
	vector<PlayerMissileTurret> PlayerMissileTurrets;
	vector<PlayerBurstTurret> PlayerBurstTurrets;
	vector<PlayerAntiProjectileTurret> PlayerAntiProjectileTurrets;
	vector<PlayerBurstMissile> PlayerBurstMissiles;
	vector<PlayerBurstProjectile> PlayerBurstProjectiles;
	vector<PlayerMissile> PlayerMissiles;
	vector<EnemySmallShip> EnemySmallShips;
	vector<EnemyMediumShip> EnemyMediumShips;
	vector<EnemyLargeShip> EnemyLargeShips;
	vector<EnemyBlasterTurret> EnemyBlasterTurrets;
	vector<EnemyMissileTurret> EnemyMissileTurrets;
	vector<EnemyProjectileTurret> EnemyProjectileTurrets;
	vector<EnemyAntiProjectileTurret> EnemyAntiProjectileTurrets;
	vector<EnemyMissile> EnemyMissiles;
	vector<EnemyProjectile> EnemyProjectiles;

	//Keeps track of Single and HUD objects
	vector<NormalSprite> NormalSprites;
	vector<NormalText> NormalTexts;
	vector<HealthBar> HealthBars;
	vector<PointsCount> PointsCounts;
	vector<Cursor> Cursors;
	vector<Button> Buttons;

	//All textures used
	unsigned TestTexture;
	unsigned TestAnimatedTexture;
	unsigned PlayerTexture;
	unsigned PlayerBulletTexture;
	unsigned EnemyBulletTexture;
	unsigned EnemyBulletTexture2;
	unsigned EnemyBulletTexture3;
	unsigned PlayerBulletHitTexture;
	unsigned PlayerBulletHitTexture2;
	unsigned PlayerBulletHitTexture3;
	unsigned PlayerShipExplodeTexture;
	unsigned EnemyBulletHitTexture;
	unsigned EnemyBulletHitTexture2;
	unsigned EnemyBulletHitTexture3;
	unsigned EnemyShipExplodeTexture;
	unsigned EnemyShipExplodeTexture2;
	unsigned EnemyShipExplodeTexture3;
	unsigned Rock1Texture;
	unsigned Rock2Texture;
	unsigned Rock3Texture;
	unsigned SmallEnemyTexture;
	unsigned SmallEnemyTexture2;
	unsigned SmallEnemyTexture3;
	unsigned HealthBarTexture;
	unsigned HeartTexture;
	unsigned LetterTexture;
	unsigned MouseTexture;
	unsigned FireRateUpTexture;
	unsigned HealUpTexture;
	unsigned LifeUpTexture;
	unsigned SpeedUpTexture;
	//Mode 2
	unsigned EnemyMissleTexture;
	unsigned EnemyProjectileTexture;
	unsigned MediumEnemyTexture;
	unsigned LargeEnemyTexture;
	unsigned DreadnoughtCapitalShipTexture;
	unsigned EnemyAntiProjectileTurretTexture;
	unsigned EnemyBlasterTurretTexture;
	unsigned EnemyMissleTurretTexture;
	unsigned EnemyProjectileTurretTexture;
	unsigned PlayerBurstTexture;
	unsigned PlayerBurstProjectileTexture;
	unsigned PlayerMissleTexture;
	unsigned PlayerAntiProjectileTurretTexture;
	unsigned PlayerBlasterTurretTexture;
	unsigned PlayerBurstTurretTexture;
	unsigned PlayerMissleTurretTexture;
	unsigned BlasterUpTexture;
	unsigned BurstUpTexture;
	unsigned EnergyReplenishUpTexture;
	unsigned LifeUpMode2Texture;
	unsigned MisslesUpTexture;
	unsigned ShieldTexture;
	unsigned BlasterBarTexture;
	unsigned BurstBarTexture;
	unsigned MissileBarTexture;
	unsigned ShieldBarTexture;
	unsigned LogoTexture;
};
//End Of Global Data