#include "Vector2.h"
#include "GameFunction.h"
#include "KeyCodeInput.h"
#include "sfwdraw.h"
#include "GameObject.h"
#include <iostream>
#include <cstring>

using namespace sfw;
using std::cin;
using std::cout;
using std::endl;

char GetkeyPressed()
{
	if (getKey(Keycode_A)) return 'a';
	else if (getKey(Keycode_B)) return 'b';
	else if (getKey(Keycode_C)) return 'c';
	else if (getKey(Keycode_D)) return 'd';
	else if (getKey(Keycode_E)) return 'e';
	else if (getKey(Keycode_F)) return 'f';
	else if (getKey(Keycode_G)) return 'g';
	else if (getKey(Keycode_H)) return 'h';
	else if (getKey(Keycode_I)) return 'i';
	else if (getKey(Keycode_J)) return 'j';
	else if (getKey(Keycode_K)) return 'k';
	else if (getKey(Keycode_L)) return 'l';
	else if (getKey(Keycode_M)) return 'm';
	else if (getKey(Keycode_N)) return 'n';
	else if (getKey(Keycode_O)) return 'o';
	else if (getKey(Keycode_P)) return 'p';
	else if (getKey(Keycode_Q)) return 'q';
	else if (getKey(Keycode_R)) return 'r';
	else if (getKey(Keycode_S)) return 's';
	else if (getKey(Keycode_T)) return 't';
	else if (getKey(Keycode_U)) return 'u';
	else if (getKey(Keycode_V)) return 'v';
	else if (getKey(Keycode_W)) return 'w';
	else if (getKey(Keycode_X)) return 'x';
	else if (getKey(Keycode_Y)) return 'y';
	else if (getKey(Keycode_Z)) return 'z';
	else if (getKey(Keycode_1)) return '1';
	else if (getKey(Keycode_2)) return '2';
	else if (getKey(Keycode_3)) return '3';
	else if (getKey(Keycode_4)) return '4';
	else if (getKey(Keycode_5)) return '5';
	else if (getKey(Keycode_6)) return '6';
	else if (getKey(Keycode_7)) return '7';
	else if (getKey(Keycode_8)) return '8';
	else if (getKey(Keycode_9)) return '9';
	else if (getKey(Keycode_0)) return '0';
	else if (getKey(Keycode_SPACE)) return ' ';
}