#pragma once
#include "Vector2.h"

struct GlobalData;

class Sprite
{
protected:
	//Texture//
	Vector2 position;
	unsigned theTexture;
	float textureWidth;
	float textureHeight;
	float textureAngle;
	bool textureCentered;
	//Animation//
	int startingFrame; //The starting current frame after a loop
	int currentFrame; //Animation Frame
	int maxFrame; //The Max Animation Frame
	float AnimationTimer; //Counts using deltatime
	float frameRate; //Speed of frame change
public:
	Sprite();
	~Sprite();
	Vector2 GetPosition();
	void SetPosition(Vector2 newPosition);
	void SetPosition(float x, float y);
	int GetStartingFrame();
	void SetStartingFrame(int newStartingFrame);
	int GetCurrentFrame();
	void SetCurrentFrame(int newCurrentFrame);
	int GetMaxFrame();
	void SetMaxFrame(int newMaxFrame);
	float GetFrameRate();
	void SetFrameRate(float newFrameRate);
	void ResetFrame(); //Reset current frame back to 0
	void SetTextureSettings(float width, float height, float angle, bool centered);
	void SetTexture(unsigned newTexture);
	void SetTexture(unsigned newTexture, int amountOfFrames); //Used for animation
	virtual void RenderTexture();
	virtual void Animate(); //Animation (Sprites must be in a single sprite sheet)
	virtual void OnUpdateLogic(GlobalData* gd);
	virtual void ResetAll();
};

