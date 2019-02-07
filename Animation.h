#pragma once
#include <FastLED.h>
//#include "Mover.h"
//#include "Strobe.h"

extern const int NUM_LEDS;
extern const uint8_t FRAMES_PER_SECOND;
extern struct CRGB leds[];

class Animation
{
private:

protected:
	uint8_t hue;
	uint8_t prevHue;
	uint8_t hueSpeed;
	uint8_t brightness;

	uint16_t rangeStart;
	uint16_t rangeEnd;

	uint8_t state;

	bool reflect;

public:

	Animation();
	Animation(uint8_t newHue, uint8_t newHueSpeed);
	Animation(uint8_t newHue, uint8_t newHueSpeed, uint8_t newBrightness);
	Animation(uint8_t newHue, uint8_t newHueSpeed, uint8_t newBrightness, uint16_t newRangeStart, uint16_t newRangeEnd);
	~Animation();

	void SetHue(uint8_t newHue);
	void SetHue(uint8_t newHue, uint8_t newHueSpeed);

	void SetBrightness(uint8_t newBrightness);

	void SetRange(uint16_t newRangeStart, uint16_t newRangeEnd);

	virtual void Update();
	void Display();

	virtual void SetSpeed(float newSpeed);

	virtual void Bounce();
	virtual void Grow(float amount);
	virtual void Shrink(float amount);
	virtual void WobbleSize(int min1, int max1, int frequency1, int min2=0, int max2=0, int frequency2=0, int min3=0, int max3=0, int frequency3=0, int min4=0, int max4=0, int frequency4=0);
	virtual void WobbleSpeed(int min1, int max1, int frequency1, int min2 = 0, int max2 = 0, int frequency2 = 0, int min3 = 0, int max3 = 0, int frequency3 = 0, int min4 = 0, int max4 = 0, int frequency4 = 0);

};

