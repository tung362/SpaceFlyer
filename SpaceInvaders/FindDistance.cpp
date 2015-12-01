#include "Vector2.h"
#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

float FindDistance(Vector2 position1, Vector2 position2)
{
	return sqrtf((position2.x - position1.x)*(position2.x - position1.x) + (position2.y - position1.y)*(position2.y - position1.y));
}