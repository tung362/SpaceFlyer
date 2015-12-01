#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;

void DrawBox(Vector2 Position, float Height, float Width)
{
	drawLine(Position.x - Width / 2, Position.y + Height / 2, Position.x + Width / 2, Position.y + Height / 2);
	drawLine(Position.x + Width / 2, Position.y + Height / 2, Position.x + Width / 2, Position.y - Height / 2);
	drawLine(Position.x + Width / 2, Position.y - Height / 2, Position.x - Width / 2, Position.y - Height / 2);
	drawLine(Position.x - Width / 2, Position.y - Height / 2, Position.x - Width / 2, Position.y + Height / 2);
}
