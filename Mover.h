#pragma once
#include "Animation.h"
class Mover :
	public Animation
{
private:
	float position;
	float speed;
	float size;

	float end1;
	float end2;

	float prevEnd1;
	float prevEnd2;
	
	bool bounce;
public:
	Mover(float newPosition, float newSpeed, float newSize, bool newBounce);
	~Mover();

	void Update();

	void SetSpeed(float newSpeed);
	void Grow(float amount);
	void Shrink(float amount);

	void Bounce();

	void ErasePrevFrame();
	void UpdatePosition();
	void Draw();
};

