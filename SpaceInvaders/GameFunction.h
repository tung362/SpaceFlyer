#pragma once
#include "Vector2.h"
#include "GlobalData.h"

void CreateDefaultGlobalData(GlobalData* gd);
void CreateNonLevelObjects(GlobalData* gd);
//Mode 1
void CreateMap(GlobalData* gd);
void NamePickUpdate(GlobalData* gd);
void Mode1Update(GlobalData* gd);
void Mode1PauseUpdate(GlobalData* gd);
//Mode 2
void CreateMapMode2(GlobalData* gd);
void Mode2Update(GlobalData* gd);
void Mode2PauseUpdate(GlobalData* gd);
//
void ResetMap(GlobalData* gd, bool CreateText);
void DrawLineBox(Vector2 Position, float Height, float Width);
void DrawLineTriangle(Vector2 Position, float Height, float Width);
int Randint(int Min, int Max); //Random int
float Randint(float Min, float Max); //Random float
float FindDistance(Vector2 position1, Vector2 position2);
char GetkeyPressed();
Vector2 RotatePoint(float CenterPointX, float CenterPointY, float Angle, Vector2 NewPoint); //Returns a new point depending on angle (Float)
void WinLose(GlobalData* gd, int ScreenID);
void SplashScreenState(GlobalData* gd);
void MainMenuState(GlobalData* gd);
void InstructionState(GlobalData* gd);
void Instruction2State(GlobalData* gd);
void AboutState(GlobalData* gd);
void HighScoreState(GlobalData* gd);