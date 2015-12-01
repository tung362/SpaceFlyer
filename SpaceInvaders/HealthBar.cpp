#include "GameFunction.h"
#include "GameObject.h"
#include "GLobalData.h"
#include "sfwdraw.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

HealthBar::HealthBar()
{
	ScreenID = 10;
	healthType = 1;
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);
	ObjectX = position.x;
	FirstWidth = textureWidth;
	FirstHeight = textureHeight;
}

HealthBar::HealthBar(int newScreenID, int newHealthType, unsigned newHandle, int amountOfFrames, Vector2 newPosition, float newHeight, float newWidth, float newAngle)
{
	ScreenID = newScreenID;
	healthType = newHealthType;
	theTexture = newHandle;
	maxFrame = amountOfFrames - 1;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	ObjectX = position.x;
	FirstWidth = textureWidth;
	FirstHeight = textureHeight;
}

HealthBar::~HealthBar()
{
}

int HealthBar::GetScreenID()
{
	return ScreenID;
}

int HealthBar::GetHealthType()
{
	return healthType;
}

void HealthBar::OnUpdateLogic(GlobalData * gd)
{
	Vector2 objectPosition = position;
	float progress;
	if(healthType == 1) progress = gd->Players[0].GetHealth() / gd->Players[0].GetMaxHealth();
	else if (healthType == 2) progress = gd->PlayerMode2s[0].GetHealth() / gd->PlayerMode2s[0].GetMaxHealth();
	else if (healthType == 3) progress = gd->PlayerMode2s[0].GetShield() / gd->PlayerMode2s[0].GetMaxShield();
	else if (healthType == 4) progress = gd->BlasterUpgrade / gd->MaxBlasterUpgrade;
	else if (healthType == 5) progress = gd->MissileUpgrade / gd->MaxMissileUpgrade;
	else if (healthType == 6) progress = gd->BurstUpgrade / gd->MaxBurstUpgrade;
	float objectAdjust = (1 - progress) * 50.4f; //Adjust how much X is moved when healthbar goes down or up
	float newPosition = (ObjectX - objectAdjust);
	textureWidth = progress * FirstWidth;
	position.x = newPosition;
	Animate();
}

void HealthBar::ResetAll()
{
}
