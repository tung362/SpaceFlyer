#include "Vector2.h"
#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;

//Referenced from http://stackoverflow.com/questions/2259476/rotating-a-point-about-another-point-2d
Vector2 RotatePoint(float CenterPointX, float CenterPointY, float Angle, Vector2 NewPoint)
{
	double s = sin(Angle * (PI / 180)); //(PI / 180) = converting float into radians
	double c = cos(Angle * (PI / 180));

	// translate point back to origin:
	NewPoint.x -= CenterPointX;
	NewPoint.y -= CenterPointY;

	// rotate points
	float xnew = (float)(NewPoint.x * c - NewPoint.y * s);
	float ynew = (float)(NewPoint.x * s + NewPoint.y * c);

	// translate point back:
	NewPoint.x = xnew + CenterPointX;
	NewPoint.y = ynew + CenterPointY;
	return NewPoint;
}