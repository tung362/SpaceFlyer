#pragma once
#include "Sprite.h"
#include "Entity.h"
#include "EntityMode2.h"
#include "Vector2.h"
#include "GameStruct.h"
#include <iostream>
#include <vector>
using std::vector;

enum Level;
struct GlobalData;
class Alien;
class Bunker;
class PlayerBullet;
class EnemyBullet;
//Mode2
class PlayerBlasterTurret;
class PlayerMissileTurret;
class PlayerBurstTurret;
class PlayerAntiProjectileTurret;
class EnemySmallShip;
class EnemyMediumShip;
class EnemyLargeShip;
class EnemyMissile;
class EnemyProjectile;
class EnemyBlasterTurret;
class EnemyMissileTurret;
class EnemyProjectileTurret;
class EnemyAntiProjectileTurret;

//Space Invaders
class Player : public Entity
{
private:
	char playerName[128];
	float shootTimer;
	float fireSpeed;
	bool debugSinglePress;
	float maxHealth;
	float invincibilityTimer; //After taking damage, become invincible for a certain amount of time
	float invincibilityDuration;
	bool isInvincible;
	float flashTimer;
	float flashDuration;
	bool flash; //Flash when invincible
public:
	Player();
	Player(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed);
	~Player();
	void GetPlayerName(char* theName);
	void SetPlayerName(const char * newName);
	float GetMaxHealth();
	void SetMaxHealth(float newMaxHealth);
	float GetInvincibilityDuration();
	void SetInvincibilityDuration(float newInvincibilityDuration);
	bool GetIsInvincible();
	void SetIsInvincible(bool newIsInvincible);
	int GetBulletsShotCount(GlobalData* gd);
	void SetBulletShotCount(GlobalData* gd, int newCount);
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class Alien : public Entity
{
private:
	float fireSpeed;
	float randomFireSpeed;
	float fireTimer;
	bool destroyed;
	int alienType; //Determines alien's texture and health
	bool moveRight; //Moves right or left
	bool moveDownSwitch; //Moves Down
	float invincibilityTimer; //After taking damage, become invincible for a certain amount of time
	float invincibilityDuration;
	bool isInvincible;
	float flashTimer;
	float flashDuration;
	bool flash; //Flash when invincible
public:
	Alien();
	Alien(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, int newAlienType);
	~Alien();
	void Destroy();
	bool isDestroyed();
	float GetInvincibilityDuration();
	void SetInvincibilityDuration(float newInvincibilityDuration);
	bool GetIsInvincible();
	void SetIsInvincible(bool newIsInvincible);
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class Bunker : public Entity
{
private:
	float rotationSpeed;
	bool ReverseRotation;
	bool destroyed;
	float invincibilityTimer; //After taking damage, become invincible for a certain amount of time
	float invincibilityDuration;
	bool isInvincible;
	float flashTimer;
	float flashDuration;
	bool flash; //Flash when invincible
public:
	Bunker();
	Bunker(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~Bunker();
	void Destroy();
	bool isDestroyed();
	float GetInvincibilityDuration();
	void SetInvincibilityDuration(float newInvincibilityDuration);
	bool GetIsInvincible();
	void SetIsInvincible(bool newIsInvincible);
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class BunkerBits : public Entity
{
private:
	Vector2 moveDirection;
	float rotationSpeed;
	bool ReverseRotation;
	bool destroyed;
	float invincibilityTimer; //After taking damage, become invincible for a certain amount of time
	float invincibilityDuration;
	bool isInvincible;
	float flashTimer;
	float flashDuration;
	bool flash; //Flash when invincible
public:
	BunkerBits();
	BunkerBits(unsigned newHandle, int amountOfFrames, Vector2 newPosition, Vector2 newMoveDirection);
	~BunkerBits();
	void Destroy();
	bool isDestroyed();
	float GetInvincibilityDuration();
	void SetInvincibilityDuration(float newInvincibilityDuration);
	bool GetIsInvincible();
	void SetIsInvincible(bool newIsInvincible);
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class PlayerBullet : public Entity
{
private:
	Vector2 moveDirection;
	bool destroyed;
	float deathTimer;
	bool canDamage;
public:
	PlayerBullet();
	PlayerBullet(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection);
	~PlayerBullet();
	void Destroy();
	bool isDestroyed();
	Vector2 GetMoveDirection();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	void ResetAll();
};

class EnemyBullet : public Entity
{
private:
	int bulletType;
	Vector2 moveDirection;
	bool destroyed;
	float deathTimer;
	bool canDamage;
public:
	EnemyBullet();
	EnemyBullet(int newBulletType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection);
	~EnemyBullet();
	void Destroy();
	bool isDestroyed();
	int GetBulletType();
	Vector2 GetMoveDirection();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	void Movement(GlobalData* gd);
	void ResetAll();
};

class Powerup : public Entity
{
private:
	Vector2 moveDirection;
	//Space Invaders: 1 = speed up, 2 = heal, 3 = life up, 4 = fire rate
	//Mode 2: 1 = Blaster up, 2 = Burst up, 3 = Energy Replenish up, 4 = Life up, 5 Missile up
	int PowerupType;
	bool destroyed;
	float deathTimer;
	bool canDamage;
public:
	Powerup();
	Powerup(int newPowerupType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection);
	~Powerup();
	void Destroy();
	bool isDestroyed();
	Vector2 GetMoveDirection();
	int GetPowerupType();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	void ResetAll();
};

class HealthBar : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = lose, 16 = win, 20 = name pick, 21 = high score
	int healthType; //1 = mode one health, 2 = mode two health, 3 = mode two shield, 4 = mode two blaster, 5 = mode two missile, 6 = mode two burst
	float ObjectX; //Starting X position
	float FirstWidth;//Starting Width
	float FirstHeight;//Starting Height
public:
	HealthBar();
	HealthBar(int newScreenID, int newHealthType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newHeight, float newWidth, float newAngle);
	~HealthBar();
	int GetScreenID();
	int GetHealthType();
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class PointsCount : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = lose, 16 = win, 20 = name pick, 21 = high score
	const char *text;
	int currentCount;
	float countTimer;
	int countType; //1 = space invaders points, 2 = space invaders waves, 3 = mode two points, 4 = mode two waves
public:
	PointsCount();
	PointsCount(int newScreenID, int newCountType,unsigned newHandle, Vector2 newPosition, float newWidth, float newHeight, float newAngle);
	~PointsCount();
	int GetScreenID();
	void OnUpdateLogic(GlobalData* gd);
	void Animate();
	void ResetAll();
};


//General
class NormalSprite : public Sprite
{
public:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	NormalSprite();
	NormalSprite(int newScreenID, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newHeight, float newWidth, float newAngle);
	~NormalSprite();
	int GetScreenID();
	void ResetAll();
};

class NormalText : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	const char *text;
public:
	NormalText();
	NormalText(int newScreenID, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle);
	~NormalText();
	int GetScreenID();
	void Animate();
	void ResetAll();
};

class Cursor : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	bool debugSinglePress;
	ColliderBounds collider;
public:
	Cursor();
	Cursor(int newScreenID, unsigned newHandle, int amountOfFrames, float newHeight, float newWidth, float newAngle);
	~Cursor();
	int GetScreenID();
	void OnUpdateLogic(GlobalData* gd);
	ColliderBounds GetCollider();
	void SetCollider(float newWidth, float newHeight);
	void ResetAll();
};

class Button : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	const char *text;
	Level ToLevel; //The level the button will send the player to
	bool buttonClicked;
	unsigned int color;
	unsigned int clickColor;
	unsigned int stayColor;
	unsigned int exitColor;
	Vector2 colliderOffset;
	ColliderBounds collider;
public:
	Button();
	Button(int newScreenID, Level newToLevel, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle);
	~Button();
	int GetScreenID();
	void SetColor(unsigned int newColor);
	void SetClickColor(unsigned int newColor);
	void SetStayColor(unsigned int newColor);
	void SetExitColor(unsigned int newColor);
	void OnUpdateLogic(GlobalData* gd);
	void Animate();
	ColliderBounds GetCollider();
	void SetColliderOffset(Vector2 newOffset);
	Vector2 GetColliderOffset();
	void SetCollider(float newWidth, float newHeight);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class NamePicker : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	std::string text;
	bool singlePress;
public:
	NamePicker();
	NamePicker(int newScreenID, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle);
	~NamePicker();
	int GetScreenID();
	std::string GetText();
	void OnUpdateLogic(GlobalData* gd);
	void Animate();
	void ResetAll();
};

class HighScoreDisplay : public Sprite
{
private:
	int ScreenID; //1 = splash screen, 2 = main menu, 3 = space invaders pause menu, 4 = mode two pause menu, 5 = about, 6 = instructions, 7 = instructions2, 10 = mode one, 11 = mode two, 15 = Lose, 16 = win, 20 = name pick, 21 = high score
	std::string text;
public:
	HighScoreDisplay();
	HighScoreDisplay(int newScreenID, unsigned newHandle, Vector2 newPosition, float newWidth, float newHeight, float newAngle);
	~HighScoreDisplay();
	int GetScreenID();
	std::string GetText();
	void OnUpdateLogic(GlobalData* gd);
	void Animate();
	void ResetAll();
};

//Mode 2
class PlayerMode2 : public EntityMode2
{
private:
	float maxHealth;
	float shield;
	float maxShield;
	float shieldRechargeTimer;
	float shieldRechargeDelay;
	vector<PlayerBlasterTurret> Blasters;
	vector<PlayerMissileTurret> Missiles;
	vector<PlayerBurstTurret> Bursts;
	vector<PlayerAntiProjectileTurret> AntiProjectiles;
	float BlasterX[5], BlasterY[5];
	float MissileX[5], MissileY[5];
	float BurstX[5], BurstY[5];
	float AntiProjectileX[5], AntiProjectileY[5];
public:
	PlayerMode2();
	PlayerMode2(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd);
	~PlayerMode2();
	void CreateShipParts(GlobalData* gd); //Creates child turrets at start of game
	void CalculateDirection(GlobalData* gd);
	float GetMaxHealth();
	void SetMaxHealth(float newMaxHealth);
	float GetShield();
	void SetShield(float newShield);
	float GetMaxShield();
	void SetMaxShield(float newMaxShield);
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class PlayerBlasterTurret : public EntityMode2
{
private:
	int workingAtUpgradeNum;
	float shootTimer;
	float fireSpeed;
public:
	PlayerBlasterTurret();
	PlayerBlasterTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~PlayerBlasterTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class PlayerMissileTurret : public EntityMode2
{
private:
	int workingAtUpgradeNum;
	float shootTimer;
	float fireSpeed;
	int targetID; //1 = small enemy, 2 = medium enemy, 3 = large enemy, 4 = boss
	EnemySmallShip * target1;
	EnemyMediumShip * target2;
	EnemyLargeShip * target3;
public:
	PlayerMissileTurret();
	PlayerMissileTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~PlayerMissileTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class PlayerBurstTurret : public EntityMode2
{
private:
	int workingAtUpgradeNum;
	float shootTimer;
	float fireSpeed;
public:
	PlayerBurstTurret();
	PlayerBurstTurret(int newWorkingAtUpgradeNum, unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~PlayerBurstTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class PlayerAntiProjectileTurret : public EntityMode2
{
private:
	float shootTimer;
	float fireSpeed;
	int targetID; //1 = enemy missile, 2 = enemy projectile
	EnemyMissile * target1;
	EnemyProjectile * target2;
public:
	PlayerAntiProjectileTurret();
	PlayerAntiProjectileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~PlayerAntiProjectileTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class PlayerBurstMissile : public EntityMode2
{
private:
	Vector2 moveDirection;
	bool destroyed;
	float deathTimer;
	bool canDamage;
	float shootTimer;
	float fireSpeed;
public:
	PlayerBurstMissile();
	PlayerBurstMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection);
	~PlayerBurstMissile();
	void Destroy();
	bool isDestroyed();
	Vector2 GetMoveDirection();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Shoot(GlobalData* gd);
	void Movement(GlobalData* gd);
	void ResetAll();
};

class PlayerBurstProjectile : public EntityMode2
{
private:
	Vector2 moveDirection;
	bool destroyed;
	float deathTimer;
	bool canDamage;
public:
	PlayerBurstProjectile();
	PlayerBurstProjectile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, Vector2 newMoveDirection);
	~PlayerBurstProjectile();
	void Destroy();
	bool isDestroyed();
	Vector2 GetMoveDirection();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	void ResetAll();
};

class PlayerMissile : public EntityMode2
{
private:
	bool destroyed;
	float deathTimer;
	bool canDamage;
	int targetID; //1 = small enemy, 2 = medium enemy, 3 = large enemy, 4 = boss
	EnemySmallShip * target1;
	EnemyMediumShip * target2;
	EnemyLargeShip * target3;
public:
	PlayerMissile();
	PlayerMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, int newTargetID, EnemySmallShip * newTarget);
	PlayerMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, int newTargetID, EnemyMediumShip * newTarget);
	PlayerMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, int newTargetID, EnemyLargeShip * newTarget);
	~PlayerMissile();
	void Destroy();
	bool isDestroyed();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

//Mode 2 enemy
class EnemySmallShip : public EntityMode2
{
private:
	bool destroyed;
	vector<EnemyBlasterTurret> Blasters;
	float BlasterX[2], BlasterY[2];
public:
	EnemySmallShip();
	EnemySmallShip(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd);
	~EnemySmallShip();
	void CreateShipParts(GlobalData* gd); //Creates child turrets at start of game
	void CalculateDirection(GlobalData* gd);
	void Destroy();
	bool isDestroyed();
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class EnemyMediumShip : public EntityMode2
{
private:
	bool destroyed;
	vector<EnemyBlasterTurret> Blasters;
	vector<EnemyMissileTurret> Missiles;
	vector<EnemyAntiProjectileTurret> AntiProjectiles;
	float BlasterX[2], BlasterY[2];
	float MissileX[2], MissileY[2];
	float AntiProjectileX[1], AntiProjectileY[1];
public:
	EnemyMediumShip();
	EnemyMediumShip(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd);
	~EnemyMediumShip();
	void CreateShipParts(GlobalData* gd); //Creates child turrets at start of game
	void CalculateDirection(GlobalData* gd);
	void Destroy();
	bool isDestroyed();
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class EnemyLargeShip : public EntityMode2
{
private:
	bool destroyed;
	vector<EnemyBlasterTurret> Blasters;
	vector<EnemyMissileTurret> Missiles;
	vector<EnemyProjectileTurret> Projectiles;
	vector<EnemyAntiProjectileTurret> AntiProjectiles;
	float BlasterX[2], BlasterY[2];
	float MissileX[4], MissileY[4];
	float ProjectileX[5], ProjectileY[5];
	float AntiProjectileX[4], AntiProjectileY[4];
	float targetChangeTimer;
	float targetChangeDelay;
	float randomDelay;
	Vector2 randomTargetPos;
public:
	EnemyLargeShip();
	EnemyLargeShip(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, GlobalData* gd);
	~EnemyLargeShip();
	void CreateShipParts(GlobalData* gd); //Creates child turrets at start of game
	void CalculateDirection(GlobalData* gd);
	void Destroy();
	bool isDestroyed();
	void Movement(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class EnemyBlasterTurret : public EntityMode2
{
private:
	float shootTimer;
	float fireSpeed;
	bool runOnce;
	PlayerMode2 * target;
public:
	EnemyBlasterTurret();
	EnemyBlasterTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~EnemyBlasterTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class EnemyMissileTurret : public EntityMode2
{
private:
	float shootTimer;
	float fireSpeed;
	bool runOnce;
	PlayerMode2 * target;
public:
	EnemyMissileTurret();
	EnemyMissileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~EnemyMissileTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class EnemyProjectileTurret : public EntityMode2
{
private:
	float shootTimer;
	float fireSpeed;
	bool runOnce;
	PlayerMode2 * target;
public:
	EnemyProjectileTurret();
	EnemyProjectileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~EnemyProjectileTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class EnemyAntiProjectileTurret : public EntityMode2
{
private:
	float shootTimer;
	float fireSpeed;
	PlayerMissile * target;
public:
	EnemyAntiProjectileTurret();
	EnemyAntiProjectileTurret(unsigned newHandle, int amountOfFrames, Vector2 newPosition);
	~EnemyAntiProjectileTurret();
	void Movement(GlobalData* gd);
	void Shoot(GlobalData* gd);
	void OnUpdateLogic(GlobalData* gd);
	void ResetAll();
};

class EnemyMissile : public EntityMode2
{
private:
	bool destroyed;
	float deathTimer;
	bool canDamage;
	bool runOnce;
	PlayerMode2 * target;
public:
	EnemyMissile();
	EnemyMissile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, PlayerMode2 * newTarget);
	~EnemyMissile();
	void Destroy();
	bool isDestroyed();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};

class EnemyProjectile : public EntityMode2
{
private:
	bool destroyed;
	float deathTimer;
	bool canDamage;
	bool runOnce;
	PlayerMode2 * target;
public:
	EnemyProjectile();
	EnemyProjectile(unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newSpeed, float newAngle, PlayerMode2 * newTarget);
	~EnemyProjectile();
	void Destroy();
	bool isDestroyed();
	bool GetCanDamage();
	void SetCanDamage(bool newCanDamage);
	ColliderBounds GetCollider();
	void Movement(GlobalData* gd);
	template<typename T>
	bool CollisionCheck(T & other);
	void ResetAll();
};