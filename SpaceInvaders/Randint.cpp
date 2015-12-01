#include "GameFunction.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

int Randint(int Min, int Max)
{
	return Min + (rand() % (Max - Min + 1)); //Got From http://stackoverflow.com/questions/5008804/generating-random-integer-from-a-range
}

float Randint(float Min, float Max) //Got From http://stackoverflow.com/questions/5289613/generate-random-float-between-two-floats
{
	return Min + (((float)rand()) / (float)RAND_MAX * (Max - Min));
}