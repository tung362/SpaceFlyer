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

Button::Button()
{
	position = Vector2(600, 40);
	SetTextureSettings(20.0f, 40.0f, 0, true);
	color = WHITE;
	clickColor = BLUE;
	stayColor = RED;
	exitColor = WHITE;
	buttonClicked = false;
}

Button::Button(int newScreenID, Level newToLevel, unsigned newHandle, const char *newText, Vector2 newPosition, float newWidth, float newHeight, float newAngle)
{
	ScreenID = newScreenID;
	ToLevel = newToLevel;
	theTexture = newHandle;
	text = newText;
	position = newPosition;
	SetTextureSettings(newWidth, newHeight, newAngle, true);
	color = WHITE;
	clickColor = BLUE;
	stayColor = RED;
	exitColor = WHITE;
	buttonClicked = false;
}

Button::~Button()
{
}

int Button::GetScreenID()
{
	return ScreenID;
}

void Button::SetColor(unsigned int newColor)
{
	color = newColor;
}

void Button::SetClickColor(unsigned int newColor)
{
	clickColor = newColor;
}

void Button::SetStayColor(unsigned int newColor)
{
	stayColor = newColor;
}

void Button::SetExitColor(unsigned int newColor)
{
	exitColor = newColor;
}

void Button::OnUpdateLogic(GlobalData * gd)
{
	//Displays collider
	if ((gd)->DebugMode == true)
	{
		double radians = textureAngle * (PI / 180);
		double degrees = 180 * radians / PI;
		float colliderAngle;
		colliderAngle = (float)fmod(degrees, 180);

		Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
		Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
		Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
		Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

		drawLine(BottomRight.x, BottomRight.y, TopLeft.x, TopLeft.y);
		drawLine(BottomLeft.x, BottomLeft.y, TopRight.x, TopRight.y);
	}

	//Collision check
	for (unsigned int i = 0; i < (gd)->Cursors.size(); ++i)
	{
		if ((gd)->Cursors[i].GetScreenID() == ScreenID)
		{
			if (CollisionCheck<Cursor>((gd)->Cursors[i]) == true)
			{
				if (getMouseButton(MOUSE_BUTTON_RIGHT) == true)
				{
					color = clickColor; //Clicked on button
					buttonClicked = true;
				}
				else color = stayColor; //Cursor just stays

				//If no longer holding down on mouse after clicking
				if (buttonClicked == true && getMouseButton(MOUSE_BUTTON_RIGHT) == false)
				{
					if (ToLevel == MainMenu)
					{
						//If mode one, also record data to text file, else don't record data
						if(ScreenID == 3) ResetMap(gd, true);
						else ResetMap(gd, false);

						(gd)->CurrentGameLevel = ToLevel; //Exit
						buttonClicked = false;
					}
					else
					{
						(gd)->CurrentGameLevel = ToLevel; //Resume
						buttonClicked = false;
					}
				}
			}
			else
			{
				color = exitColor; //Cursor isnt colliding
				buttonClicked = false;
			}
		}
	}

	Animate();
}

void Button::Animate()
{
	drawString(theTexture, text, position.x, position.y, textureWidth, textureHeight, textureAngle, '\0', color);
}

ColliderBounds Button::GetCollider()
{
	return collider;
}

void Button::SetColliderOffset(Vector2 newOffset)
{
	colliderOffset = newOffset;
}

Vector2 Button::GetColliderOffset()
{
	return colliderOffset;
}

void Button::SetCollider(float newWidth, float newHeight)
{
	collider = { newWidth , newHeight };
}

template<typename T>
bool Button::CollisionCheck(T & other)
{
	double radians = textureAngle * (PI / 180);
	double degrees = 180 * radians / PI;
	float colliderAngle;
	colliderAngle = (float)fmod(degrees, 180);

	//Gets enemy collider vertex
	float otherTop = other.GetPosition().y + other.GetCollider().height / 2;
	float otherBottom = other.GetPosition().y - other.GetCollider().height / 2;
	float otherRight = other.GetPosition().x + other.GetCollider().width / 2;
	float otherLeft = other.GetPosition().x - other.GetCollider().width / 2;

	//Gets bunker collider vertex (Position depends on the angle)
	Vector2 TopLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Left
	Vector2 BottomRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Right
	Vector2 TopRight = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x + collider.width / 2) + colliderOffset.x, (position.y + collider.height / 2) + colliderOffset.y)); //Top Right
	Vector2 BottomLeft = RotatePoint(position.x + colliderOffset.x, position.y + colliderOffset.y, colliderAngle, Vector2((position.x - collider.width / 2) + colliderOffset.x, (position.y - collider.height / 2) + colliderOffset.y)); //Bottom Left

																																						 //Collision
	if (colliderAngle <= 90)
	{
		if (((otherTop <= TopLeft.y && otherTop >= BottomRight.y) || (otherBottom <= TopRight.y && otherBottom >= BottomLeft.y)) && //Top, Bottom
			((otherRight <= BottomRight.x && otherRight >= TopLeft.x) || (otherLeft <= BottomRight.x && otherLeft >= TopLeft.x))) return true; //Right, Left
		else return false;
	}
	else
	{
		if (((otherTop <= BottomRight.y && otherTop >= BottomLeft.y) || (otherBottom <= BottomRight.y && otherBottom >= TopLeft.y)) && //Top, Bottom
			((otherRight <= BottomLeft.x && otherRight >= TopRight.x) || (otherLeft <= BottomLeft.x && otherLeft >= TopRight.x))) return true; //Right, Left
		else return false;
	}
}

void Button::ResetAll()
{
}
