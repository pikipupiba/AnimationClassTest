#include "Strobe.h"

Strobe::Strobe(long newOnTime, long newOffTime){
	onTime = newOnTime;
	offTime = newOffTime;

	hue = 120;
	prevHue = hue;
	hueSpeed = 1;
	brightness = 255;
	rangeStart = 0;
	rangeEnd = NUM_LEDS - 1;
}

Strobe::~Strobe(){
}

void Strobe::Update(){
	if (isOn && millis() - lastMillis > onTime) {
		ErasePrevFrame();
	}
	else if (isOn == false && millis() - lastMillis > offTime) {
		Draw();
	}
}

void Strobe::ErasePrevFrame(){
	for (int i = 0; i < NUM_LEDS - 1; i++) {
		leds[i] -= CHSV(prevHue, 255, brightness);
	}
	isOn = false;
	lastMillis = millis();
	hue += hueSpeed;
}

void Strobe::Draw(){
	for (int i = rangeStart; i < rangeEnd-1; i++) {
		leds[i] += CHSV(hue, 255, brightness);
	}
	//fill_solid(leds, NUM_LEDS, hue); // *** Sometimes was dimming
	isOn = true;
	lastMillis = millis();

	prevHue = hue;
}
