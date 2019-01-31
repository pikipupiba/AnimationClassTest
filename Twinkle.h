#pragma once
#include "Animation.h"
class Twinkle :
	public Animation
{
private:
	uint8_t rate;
	uint8_t fade;
	uint16_t twinkles[20][2];
public:
	Twinkle(uint8_t newRate,uint8_t newFade);
	~Twinkle();

	void DimPrevFrame();
	void Draw();

	void Update();

	void UpdateTwinkles();
};

