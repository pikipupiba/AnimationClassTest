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
	void WobbleSize(int min1, int max1, int frequency1, int min2, int max2, int frequency2, int min3, int max3, int frequency3, int min4, int max4, int frequency4);
	void WobbleSpeed(int min1, int max1, int frequency1, int min2, int max2, int frequency2, int min3, int max3, int frequency3, int min4, int max4, int frequency4);


	void ErasePrevFrame();
	void UpdatePosition();
	void Draw();

};

