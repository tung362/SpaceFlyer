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

void CreateNonLevelObjects(GlobalData* gd)
{
	if ((gd)->CreateNonLevelObjects == true)
	{
		//Splash Screen
		NormalSprite logo(1, (gd)->LogoTexture, 1, Vector2(600, 400), 900.0f, 900.0f, 0); //Logo
		(gd)->NormalSprites.push_back(logo);

		//Main Menu
		NormalSprite mainMenuLogo(2, (gd)->LogoTexture, 1, Vector2(600, 650), 500.0f, 500.0f, 0); //Logo
		(gd)->NormalSprites.push_back(mainMenuLogo);

		Cursor mainMenuCursor(2, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		mainMenuCursor.SetFrameRate(0.1f);
		mainMenuCursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(mainMenuCursor);

		Button mainMenuMode1(2, SIStartGame, (gd)->LetterTexture, "Mode 1", Vector2(500, 500), 25, 25, 0); //Mode 1
		mainMenuMode1.SetColliderOffset(Vector2(70, -10));
		mainMenuMode1.SetCollider(140, 40);
		(gd)->Buttons.push_back(mainMenuMode1);

		Button mainMenuMode2(2, M2StartGame, (gd)->LetterTexture, "Mode 2", Vector2(500, 420), 25, 25, 0); //Mode 2
		mainMenuMode2.SetColliderOffset(Vector2(70, -10));
		mainMenuMode2.SetCollider(140, 40);
		(gd)->Buttons.push_back(mainMenuMode2);

		Button mainMenuInstruction(2, Instruction, (gd)->LetterTexture, "Instructions", Vector2(430, 340), 25, 25, 0); //Instruction
		mainMenuInstruction.SetColliderOffset(Vector2(150, -10));
		mainMenuInstruction.SetCollider(300, 40);
		(gd)->Buttons.push_back(mainMenuInstruction);

		Button mainMenuAbout(2, About, (gd)->LetterTexture, "About", Vector2(510, 260), 25, 25, 0); //Mode 2
		mainMenuAbout.SetColliderOffset(Vector2(60, -10));
		mainMenuAbout.SetCollider(130, 40);
		(gd)->Buttons.push_back(mainMenuAbout);

		Button mainMenuHighScore(2, HighScore, (gd)->LetterTexture, "High Score", Vector2(450, 180), 25, 25, 0); //High score
		mainMenuHighScore.SetColliderOffset(Vector2(120, -10));
		mainMenuHighScore.SetCollider(240, 40);
		(gd)->Buttons.push_back(mainMenuHighScore);

		Button mainMenuExit(2, Exit, (gd)->LetterTexture, "Exit", Vector2(520, 100), 25, 25, 0); //Exit
		mainMenuExit.SetColliderOffset(Vector2(50, -10));
		mainMenuExit.SetCollider(110, 40);
		(gd)->Buttons.push_back(mainMenuExit);

		//Instructions
		Cursor instructionsCursor(6, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		instructionsCursor.SetFrameRate(0.1f);
		instructionsCursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(instructionsCursor);

		Button instructionsNext(6, Instruction2, (gd)->LetterTexture, "Next", Vector2(1050, 120), 25, 25, 0); //Back
		instructionsNext.SetColliderOffset(Vector2(50, -10));
		instructionsNext.SetCollider(90, 30);
		(gd)->Buttons.push_back(instructionsNext);

		Button instructionsBack(6, MainMenu, (gd)->LetterTexture, "Back", Vector2(1050, 50), 25, 25, 0); //Back
		instructionsBack.SetColliderOffset(Vector2(50, -10));
		instructionsBack.SetCollider(90, 30);
		(gd)->Buttons.push_back(instructionsBack);

		NormalText instructionsTitle(6, (gd)->LetterTexture, "Instructions(Mode 1)", Vector2(350, 780), 25, 25, 0); //Title
		(gd)->NormalTexts.push_back(instructionsTitle);

		NormalText instructionsSubTitle(6, (gd)->LetterTexture, "Controls:", Vector2(50, 650), 23, 23, 0); //SubTitle
		(gd)->NormalTexts.push_back(instructionsSubTitle);

		NormalText instructionsDialog1(6, (gd)->LetterTexture, "A - Move Left", Vector2(50, 600), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog1);

		NormalText instructionsDialog2(6, (gd)->LetterTexture, "D - Move Right", Vector2(50, 550), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog2);

		NormalText instructionsDialog3(6, (gd)->LetterTexture, "Space - Shoot", Vector2(50, 500), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog3);

		NormalText instructionsSubTitle2(6, (gd)->LetterTexture, "description:", Vector2(50, 400), 23, 23, 0); //SubTitle
		(gd)->NormalTexts.push_back(instructionsSubTitle2);

		NormalText instructionsDialog4(6, (gd)->LetterTexture, "Destroy waves of aliens.", Vector2(50, 350), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog4);

		NormalText instructionsDialog5(6, (gd)->LetterTexture, "Collect power ups to improve fire rate, speed, health, and heal.", Vector2(50, 300), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog5);

		NormalText instructionsDialog6(6, (gd)->LetterTexture, "Don't die or let them get too close!", Vector2(50, 250), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructionsDialog6);

		//Instructions2
		Cursor instructions2Cursor(7, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		instructions2Cursor.SetFrameRate(0.1f);
		instructions2Cursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(instructions2Cursor);

		Button instructions2Back(7, MainMenu, (gd)->LetterTexture, "Back", Vector2(1050, 50), 25, 25, 0); //Back
		instructions2Back.SetColliderOffset(Vector2(50, -10));
		instructions2Back.SetCollider(90, 30);
		(gd)->Buttons.push_back(instructions2Back);

		NormalText instructions2Title(7, (gd)->LetterTexture, "Instructions(Mode 2)", Vector2(350, 780), 25, 25, 0); //Title
		(gd)->NormalTexts.push_back(instructions2Title);

		NormalText instructions2SubTitle(7, (gd)->LetterTexture, "Controls:", Vector2(50, 650), 23, 23, 0); //SubTitle
		(gd)->NormalTexts.push_back(instructions2SubTitle);

		NormalText instructions2Dialog1(7, (gd)->LetterTexture, "A - Rotate Left", Vector2(50, 600), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog1);

		NormalText instructions2Dialog2(7, (gd)->LetterTexture, "D - Rotate Right", Vector2(50, 550), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog2);

		NormalText instructions2Dialog3(7, (gd)->LetterTexture, "W - Move Forward", Vector2(50, 500), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog3);

		NormalText instructions2Dialog4(7, (gd)->LetterTexture, "S - Move Backward", Vector2(50, 450), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog4);

		NormalText instructions2Dialog5(7, (gd)->LetterTexture, "Mouse Left Click - Shoot", Vector2(50, 400), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog5);

		NormalText instructions2Dialog6(7, (gd)->LetterTexture, "Move Mouse - Aim", Vector2(50, 350), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog6);

		NormalText instructions2SubTitle2(7, (gd)->LetterTexture, "description:", Vector2(50, 250), 23, 23, 0); //SubTitle
		(gd)->NormalTexts.push_back(instructions2SubTitle2);

		NormalText instructions2Dialog7(7, (gd)->LetterTexture, "Destroy waves of aliens and collect power ups.", Vector2(50, 200), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog7);

		NormalText instructions2Dialog8(7, (gd)->LetterTexture, "Don't die.", Vector2(50, 150), 18, 18, 0); //Dialog
		(gd)->NormalTexts.push_back(instructions2Dialog8);

		//About
		Cursor aboutCursor(5, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		aboutCursor.SetFrameRate(0.1f);
		aboutCursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(aboutCursor);

		Button aboutBack(5, MainMenu, (gd)->LetterTexture, "Back", Vector2(1050, 50), 25, 25, 0); //Back
		aboutBack.SetColliderOffset(Vector2(50, -10));
		aboutBack.SetCollider(90, 30);
		(gd)->Buttons.push_back(aboutBack);

		NormalText tung(5, (gd)->LetterTexture, "Made by: Tung Nguyen", Vector2(400, 400), 20, 20, 0); //Made by
		(gd)->NormalTexts.push_back(tung);

		//High Score
		Cursor highScoreCursor(21, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		highScoreCursor.SetFrameRate(0.1f);
		highScoreCursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(highScoreCursor);

		Button highScoreBack(21, MainMenu, (gd)->LetterTexture, "Back", Vector2(1050, 50), 25, 25, 0); //Back
		highScoreBack.SetColliderOffset(Vector2(50, -10));
		highScoreBack.SetCollider(90, 30);
		(gd)->Buttons.push_back(highScoreBack);

		NormalText highScoreTitle(21, (gd)->LetterTexture, "High Score", Vector2(500, 780), 25, 25, 0); //Title
		(gd)->NormalTexts.push_back(highScoreTitle);

		NormalText highScoreDialog1(21, (gd)->LetterTexture, "Highest Score:", Vector2(50, 450), 20, 20, 0); //High score dialog
		(gd)->NormalTexts.push_back(highScoreDialog1);

		HighScoreDisplay highScoreDisplayer(21, (gd)->LetterTexture, Vector2(50, 400), 18, 18, 0); //High score displayer
		(gd)->HighScoreDisplays.push_back(highScoreDisplayer);

		//Space Invaders Name Pick
		NormalText nameDialog(20, (gd)->LetterTexture, "Type out a name:", Vector2(450, 600), 20, 20, 0); //Name dialog
		(gd)->NormalTexts.push_back(nameDialog);

		NormalText nameTag(20, (gd)->LetterTexture, "Name:", Vector2(350, 400), 18, 18, 0); //Name tag
		(gd)->NormalTexts.push_back(nameTag);

		NamePicker namePicker(20, (gd)->LetterTexture, "", Vector2(440, 400), 18, 18, 0); //Name picker
		(gd)->NamePickers.push_back(namePicker);

		//Space Invaders Pause Menu
		Cursor pauseCursor(3, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		pauseCursor.SetFrameRate(0.1f);
		pauseCursor.SetCollider(40, 40);
		(gd)->Cursors.push_back(pauseCursor);

		Button pauseResume(3, SIStartGame, (gd)->LetterTexture, "Resume", Vector2(500, 400), 30, 30, 0); //Resume //Mode1
		pauseResume.SetColliderOffset(Vector2(90, -10));
		pauseResume.SetCollider(155, 40);
		(gd)->Buttons.push_back(pauseResume);

		Button pauseExit(3, MainMenu, (gd)->LetterTexture, "Exit", Vector2(525, 300), 30, 30, 0); //Exit
		pauseExit.SetColliderOffset(Vector2(55, -10));
		pauseExit.SetCollider(120, 40);
		(gd)->Buttons.push_back(pauseExit);

		//Mode Two Pause Menu
		Cursor pauseCursor2(4, (gd)->MouseTexture, 14, 50, 50, 0); //Mouse
		pauseCursor2.SetFrameRate(0.1f);
		pauseCursor2.SetCollider(40, 40);
		(gd)->Cursors.push_back(pauseCursor2);

		Button pauseResume2(4, M2StartGame, (gd)->LetterTexture, "Resume", Vector2(500, 400), 30, 30, 0); //Resume //Mode2
		pauseResume2.SetColliderOffset(Vector2(90, -10));
		pauseResume2.SetCollider(155, 40);
		(gd)->Buttons.push_back(pauseResume2);

		Button pauseExit2(4, MainMenu, (gd)->LetterTexture, "Exit", Vector2(525, 300), 30, 30, 0); //Exit
		pauseExit2.SetColliderOffset(Vector2(55, -10));
		pauseExit2.SetCollider(120, 40);
		(gd)->Buttons.push_back(pauseExit2);

		//Mode 1
		NormalSprite heart(10, (gd)->HeartTexture, 1, Vector2(25, 200), 35.0f, 35.0f, 0); //Heart
		(gd)->NormalSprites.push_back(heart);

		NormalSprite healthbarBG(10, (gd)->HealthBarTexture, 1, Vector2(95, 200), 18.0f, 100.0f, 0); //Heathbar bg
		(gd)->NormalSprites.push_back(healthbarBG);

		HealthBar healthbar(10, 1, (gd)->HealthBarTexture, 1, Vector2(95, 200), 18.0f, 100.0f, 0); //Heathbar
		(gd)->HealthBars.push_back(healthbar);

		NormalText points(10, (gd)->LetterTexture, "Points:", Vector2(15, 175), 18, 18, 0); //Points
		(gd)->NormalTexts.push_back(points);

		PointsCount pointCount(10, 1, (gd)->LetterTexture, Vector2(140, 173), 15, 15, 0); //Points count
		(gd)->PointsCounts.push_back(pointCount);

		NormalText wave(10, (gd)->LetterTexture, "Wave:", Vector2(15, 150), 18, 18, 0); //Wave
		(gd)->NormalTexts.push_back(wave);

		PointsCount waveCount(10, 2, (gd)->LetterTexture, Vector2(105, 147), 15, 15, 0); //Wave count
		(gd)->PointsCounts.push_back(waveCount);


		//Mode 2
		Cursor mode2Cursor(11, (gd)->MouseTexture, 14, 25, 25, 0); //Mouse
		mode2Cursor.SetFrameRate(0.1f);
		mode2Cursor.SetCollider(10, 10);
		(gd)->Cursors.push_back(mode2Cursor);

		NormalText mode2wave(11, (gd)->LetterTexture, "Wave:", Vector2(15, 140), 18, 18, 0); //Wave
		(gd)->NormalTexts.push_back(mode2wave);

		PointsCount mode2WaveCount(11, 4, (gd)->LetterTexture, Vector2(105, 137), 15, 15, 0); //Points count
		(gd)->PointsCounts.push_back(mode2WaveCount);

		//
		NormalSprite shieldMode2(11, (gd)->ShieldTexture, 1, Vector2(25, 200), 35.0f, 35.0f, 0);
		(gd)->NormalSprites.push_back(shieldMode2);

		NormalSprite shieldbarBGMode2(11, (gd)->ShieldBarTexture, 1, Vector2(95, 200), 18.0f, 100.0f, 0);
		(gd)->NormalSprites.push_back(shieldbarBGMode2);

		HealthBar shieldbarMode2(11, 3, (gd)->ShieldBarTexture, 1, Vector2(95, 200), 18.0f, 100.0f, 0);
		(gd)->HealthBars.push_back(shieldbarMode2);
		//
		NormalSprite heartMode2(11, (gd)->HeartTexture, 1, Vector2(25, 165), 35.0f, 35.0f, 0);
		(gd)->NormalSprites.push_back(heartMode2);

		NormalSprite healthbarBGMode2(11, (gd)->HealthBarTexture, 1, Vector2(95, 165), 18.0f, 100.0f, 0);
		(gd)->NormalSprites.push_back(healthbarBGMode2);

		HealthBar healthbarMode2(11, 2, (gd)->HealthBarTexture, 1, Vector2(95, 165), 18.0f, 100.0f, 0);
		(gd)->HealthBars.push_back(healthbarMode2);
		//
		NormalText blaster(11, (gd)->LetterTexture, "Blaster:", Vector2(15, 780), 16, 16, 0);
		(gd)->NormalTexts.push_back(blaster);

		NormalSprite blasterbarBGMode2(11, (gd)->BlasterBarTexture, 1, Vector2(195, 770), 18.0f, 100.0f, 0);
		(gd)->NormalSprites.push_back(blasterbarBGMode2);

		HealthBar blasterbarMode2(11, 4, (gd)->BlasterBarTexture, 1, Vector2(195, 770), 18.0f, 100.0f, 0);
		(gd)->HealthBars.push_back(blasterbarMode2);
		//
		NormalText missile(11, (gd)->LetterTexture, "Missile:", Vector2(500, 780), 16, 16, 0);
		(gd)->NormalTexts.push_back(missile);

		NormalSprite missilebarBGMode2(11, (gd)->MissileBarTexture, 1, Vector2(680, 770), 18.0f, 100.0f, 0);
		(gd)->NormalSprites.push_back(missilebarBGMode2);

		HealthBar missilebarMode2(11, 5, (gd)->MissileBarTexture, 1, Vector2(680, 770), 18.0f, 100.0f, 0);
		(gd)->HealthBars.push_back(missilebarMode2);
		//
		NormalText burst(11, (gd)->LetterTexture, "Burst:", Vector2(980, 780), 16, 16, 0);
		(gd)->NormalTexts.push_back(burst);

		NormalSprite burstbarBGMode2(11, (gd)->BurstBarTexture, 1, Vector2(1130, 770), 18.0f, 100.0f, 0);
		(gd)->NormalSprites.push_back(burstbarBGMode2);

		HealthBar burstbarMode2(11, 6, (gd)->BurstBarTexture, 1, Vector2(1130, 770), 18.0f, 100.0f, 0);
		(gd)->HealthBars.push_back(burstbarMode2);

		//WinLose
		NormalText lose(15, (gd)->LetterTexture, "You Lose!", Vector2(500, 400), 23, 23, 0);
		(gd)->NormalTexts.push_back(lose);

		(gd)->CreateNonLevelObjects = false;
	}
}