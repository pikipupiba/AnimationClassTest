#include "Twinkle.h"


Twinkle::Twinkle(uint8_t newRate, uint8_t newFade){
	rate = newRate;
	fade = newFade;
	
	for (int i = 0; i < 21; i++) {
		twinkles[i][0] = random16(rangeStart,rangeEnd);
		twinkles[i][1] = random8(0,brightness);
	}

	hue = 120;
	prevHue = hue;
	hueSpeed = 1;
	brightness = 255;
	rangeStart = 0;
	rangeEnd = NUM_LEDS - 1;
}

Twinkle::~Twinkle(){
}

void Twinkle::DimPrevFrame(){

	for (int i = 0; i < 21; i++) {
		if (twinkles[i][1] > 0) {
			if (twinkles[i][1] > fade) {
				twinkles[i][1] -= fade;
			}
			else {
				twinkles[i][1] = 0;
			}

			leds[twinkles[i][0]] = CHSV(hue, 255, twinkles[i][1]);
		}
	}

}

void Twinkle::Draw(){

	for (int i = 0; i < 21; i++) {
		leds[twinkles[i][0]] = CHSV(hue, 255, twinkles[i][1]);
	}

}

void Twinkle::Update(){
	
	DimPrevFrame();
	UpdateTwinkles();
	hue += hueSpeed;

}

void Twinkle::UpdateTwinkles(){

	for (int i = 0; i < 21; i++) {
		if (twinkles[i][1] == 0 && random8() < rate) {
			twinkles[i][0] = random(rangeStart, rangeEnd);
			twinkles[i][1] = brightness;

			leds[twinkles[i][0]] = CHSV(hue, 255, twinkles[i][1]);
		}
	}

}
