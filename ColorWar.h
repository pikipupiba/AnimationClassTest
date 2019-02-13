#pragma once
#include "Animation.h"
class ColorWar :
	public Animation
{
private:

	float position;
	float speed;
	float acceleration;

	uint8_t numColors;
	uint8_t color1;
	uint8_t color2;

	uint8_t colors[16][2];

	uint8_t sinOffset;

public:
	ColorWar(int newNumColors);
	~ColorWar();

	void Update();

	void UpdatePosition();
	void AdvanceBracket();
	void Draw();
	void ErasePrevFrame();

	void ColorParade();
	void Battle();
	void Flash();
	void NextColors();
};

