#pragma once
#include "Animation.h"
class Strobe :
	public Animation
{
private:
	unsigned long onTime;
	unsigned long offTime;
	unsigned long lastMillis;

	bool isOn = true;
public:
	Strobe(long newOnTime, long newOffTime);
	~Strobe();

	void Update();

	void ErasePrevFrame();
	void Draw();
};

