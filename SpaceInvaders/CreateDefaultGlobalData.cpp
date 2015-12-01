#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include "GlobalData.h"
#include <iostream>
#include <cstring>
#include <fstream>

using namespace sfw;

void CreateDefaultGlobalData(GlobalData* gd)
{
	//Default global data values
	(gd)->CurrentGameLevel = SplashScreen;
	(gd)->CreateNewMap = true;
	(gd)->HasPickedName = false;
	(gd)->CreateNonLevelObjects = true;
	(gd)->LoseGame = false;
	(gd)->WinGame = false;
	(gd)->AlienMove = false;
	(gd)->DebugMode = false;
	(gd)->WinLoseTimer = 0;
	(gd)->SplashScreenTimer = 0;
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

	//Load Textures
	(gd)->TestTexture = loadTextureMap("./Textures/sword.png");
	(gd)->TestAnimatedTexture = loadTextureMap("./Textures/sword.png", 4, 4);
	(gd)->PlayerTexture = loadTextureMap("./Textures/Player/Player.png", 4, 3);
	(gd)->PlayerBulletTexture = loadTextureMap("./Textures/PlayerBullet/PlayerBullet.png");
	(gd)->EnemyBulletTexture = loadTextureMap("./Textures/EnemyBullet/EnemyBullet.png");
	(gd)->EnemyBulletTexture2 = loadTextureMap("./Textures/EnemyBullet/EnemyBullet2.png");
	(gd)->EnemyBulletTexture3 = loadTextureMap("./Textures/EnemyBullet/EnemyBullet3.png");
	(gd)->PlayerBulletHitTexture = loadTextureMap("./Textures/PlayerBulletHit/PlayerBulletHit.png", 3, 3);
	(gd)->PlayerShipExplodeTexture = loadTextureMap("./Textures/PlayerExplode/PlayerExplode.png", 2, 2);
	(gd)->EnemyBulletHitTexture = loadTextureMap("./Textures/EnemyBulletHit/EnemyBulletHit.png", 3, 3);
	(gd)->EnemyBulletHitTexture2 = loadTextureMap("./Textures/EnemyBulletHit/EnemyBulletHit2.png", 3, 3);
	(gd)->EnemyBulletHitTexture3 = loadTextureMap("./Textures/EnemyBulletHit/EnemyBulletHit3.png", 3, 3);
	(gd)->EnemyShipExplodeTexture = loadTextureMap("./Textures/EnemyExplode/EnemyExplode.png", 2, 2);
	(gd)->EnemyShipExplodeTexture2 = loadTextureMap("./Textures/EnemyExplode/EnemyExplode2.png", 2, 2);
	(gd)->EnemyShipExplodeTexture3 = loadTextureMap("./Textures/EnemyExplode/EnemyExplode3.png", 2, 2);
	(gd)->Rock1Texture = loadTextureMap("./Textures/Rock/Rock1.png");
	(gd)->Rock2Texture = loadTextureMap("./Textures/Rock/Rock2.png");
	(gd)->Rock3Texture = loadTextureMap("./Textures/Rock/Rock3.png");
	(gd)->SmallEnemyTexture = loadTextureMap("./Textures/Enemy/SmallEnemy.png");
	(gd)->SmallEnemyTexture2 = loadTextureMap("./Textures/Enemy/SmallEnemy2.png");
	(gd)->SmallEnemyTexture3 = loadTextureMap("./Textures/Enemy/SmallEnemy3.png");
	(gd)->HealthBarTexture = loadTextureMap("./Textures/UI/HealthBar.png");
	(gd)->HeartTexture = loadTextureMap("./Textures/UI/Heart.png");
	(gd)->LetterTexture = loadTextureMap("./Textures/UI/Letters.png", 16, 16);
	(gd)->MouseTexture = loadTextureMap("./Textures/UI/Mouse/Mouse.png", 4, 4);
	(gd)->FireRateUpTexture = loadTextureMap("./Textures/Powerup/FireRateUp/FireRateUp.png", 4, 4);
	(gd)->HealUpTexture = loadTextureMap("./Textures/Powerup/HealUp/HealUp.png", 4, 4);
	(gd)->LifeUpTexture = loadTextureMap("./Textures/Powerup/LifeUp/LifeUp.png", 4, 4);
	(gd)->SpeedUpTexture = loadTextureMap("./Textures/Powerup/SpeedUp/SpeedUp.png", 4, 4);
	//Mode 2
	(gd)->EnemyMissleTexture = loadTextureMap("./Textures/Mode2/EnemyProjectiles/EnemyMissle.png");
	(gd)->EnemyProjectileTexture = loadTextureMap("./Textures/Mode2/EnemyProjectiles/EnemyProjectile.png");
	(gd)->MediumEnemyTexture = loadTextureMap("./Textures/Mode2/EnemyShips/MediumEnemy.png");
	(gd)->LargeEnemyTexture = loadTextureMap("./Textures/Mode2/EnemyShips/LargeEnemy.png");
	(gd)->DreadnoughtCapitalShipTexture = loadTextureMap("./Textures/Mode2/EnemyShips/DreadnoughtCapitalShip.png");
	(gd)->EnemyAntiProjectileTurretTexture = loadTextureMap("./Textures/Mode2/EnemyTurrets/EnemyAntiProjectileTurret.png");
	(gd)->EnemyBlasterTurretTexture = loadTextureMap("./Textures/Mode2/EnemyTurrets/EnemyBlasterTurret.png");
	(gd)->EnemyMissleTurretTexture = loadTextureMap("./Textures/Mode2/EnemyTurrets/EnemyMissleTurret.png");
	(gd)->EnemyProjectileTurretTexture = loadTextureMap("./Textures/Mode2/EnemyTurrets/EnemyProjectileTurret.png");
	(gd)->PlayerBurstTexture = loadTextureMap("./Textures/Mode2/PlayerProjectiles/PlayerBurst.png");
	(gd)->PlayerBurstProjectileTexture = loadTextureMap("./Textures/Mode2/PlayerProjectiles/PlayerBurstProjectile.png");
	(gd)->PlayerMissleTexture = loadTextureMap("./Textures/Mode2/PlayerProjectiles/PlayerMissle.png");
	(gd)->PlayerAntiProjectileTurretTexture = loadTextureMap("./Textures/Mode2/PlayerTurrets/PlayerAntiProjectileTurret.png");
	(gd)->PlayerBlasterTurretTexture = loadTextureMap("./Textures/Mode2/PlayerTurrets/PlayerBlasterTurret.png");
	(gd)->PlayerBurstTurretTexture = loadTextureMap("./Textures/Mode2/PlayerTurrets/PlayerBurstTurret.png");
	(gd)->PlayerMissleTurretTexture = loadTextureMap("./Textures/Mode2/PlayerTurrets/PlayerMissleTurret.png");
	(gd)->BlasterUpTexture = loadTextureMap("./Textures/Mode2/PowerUp/BlasterUp/BlasterUp.png", 4 ,4);
	(gd)->BurstUpTexture = loadTextureMap("./Textures/Mode2/PowerUp/BurstUnlock/BurstUnlock.png", 4, 4);
	(gd)->EnergyReplenishUpTexture = loadTextureMap("./Textures/Mode2/PowerUp/EnergyReplenish/EnergyReplenish.png", 4, 4);
	(gd)->LifeUpMode2Texture = loadTextureMap("./Textures/Mode2/PowerUp/LifeUp/LifeUp.png", 4, 4);
	(gd)->MisslesUpTexture = loadTextureMap("./Textures/Mode2/PowerUp/MisslesUnlock/MisslesUnlock.png", 4, 4);
	(gd)->ShieldTexture = loadTextureMap("./Textures/Mode2/UI/Shield.png");
	(gd)->BlasterBarTexture = loadTextureMap("./Textures/Mode2/UI/BlasterBar.png");
	(gd)->BurstBarTexture = loadTextureMap("./Textures/Mode2/UI/BurstBar.png");
	(gd)->MissileBarTexture = loadTextureMap("./Textures/Mode2/UI/MissileBar.png");
	(gd)->ShieldBarTexture = loadTextureMap("./Textures/Mode2/UI/ShieldBar.png");
	(gd)->LogoTexture = loadTextureMap("./Textures/Mode2/UI/Logo.png");
}