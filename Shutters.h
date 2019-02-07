#pragma once
#include "Animation.h"
class Shutters :
	public Animation
{
private:
	float position;
	float speed;
	float size;
	int numSegments;
	int phase;
	int increase;

	float end1;
	float end2;

	float prevEnd1;
	float prevEnd2;
	
	bool bounce;

public:
	Shutters(int newNumSegments, float newSpeed, int newIncrease, int newPhase);
	~Shutters();

	void Update();

	void SetSpeed(float newSpeed);

	void UpdatePosition();
	void Draw();
	void ErasePrevFrame();
};

