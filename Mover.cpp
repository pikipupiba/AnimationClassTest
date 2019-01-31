#include "Mover.h"

Mover::Mover(float newPosition, float newSpeed, float newSize, bool newBounce){
	
	position = newPosition;
	speed = newSpeed;
	size = newSize;
	bounce = newBounce;

	end1 = position - size / 2;
	end2 = position + size / 2;

	prevEnd1 = end1;
	prevEnd2 = end2;
	prevHue = hue;
	
	hue = 0;
	hueSpeed = 1;
	brightness = 255;
	rangeStart = 0;
	rangeEnd = NUM_LEDS-1;
	
}

Mover::~Mover(){
	ErasePrevFrame();
}

void Mover::Update(){

	ErasePrevFrame();
	UpdatePosition();
	Draw();
	
}

void Mover::SetSpeed(float newSpeed)
{
	if (speed < 0) {
		speed = -newSpeed;
	}
	else{
		speed = newSpeed;
	}
}

void Mover::ErasePrevFrame(){

	leds[(int)prevEnd1] -= CHSV(prevHue, 255, brightness*(1 - (prevEnd1 - (long)prevEnd1)));
	//leds[NUM_LEDS-(int)prevEnd1-1] -= CHSV(prevHue, 255, brightness*(1 - (prevEnd1 - (long)prevEnd1)));
	
	for (int i = prevEnd1 + 1; i < prevEnd2-1; i++){
		leds[i] -= CHSV(prevHue, 255, brightness);
		//leds[NUM_LEDS-i-1] -= CHSV(prevHue, 255, brightness);
	}

	leds[(int)prevEnd2] -= CHSV(prevHue, 255, brightness*(prevEnd2 - (long)prevEnd2));
	//leds[NUM_LEDS-(int)prevEnd2-1] -= CHSV(prevHue, 255, brightness*(prevEnd2 - (long)prevEnd2));

}

void Mover::UpdatePosition() {

	if (speed > 0 && end2 + speed + 1 > rangeEnd) {
		speed = -speed;
	}
	else if (speed < 0 && end1 < rangeStart) {
		speed = -speed;
	}

	position += speed;

	prevEnd1 = end1;
	prevEnd2 = end2;
	prevHue = hue;

	end1 = position - size / 2;
	end2 = position + size / 2;
	hue += hueSpeed;

}

void Mover::Draw(){

	leds[(int)end1] += CHSV(hue, 255, brightness*(1-(end1 - (long)end1)));
	//leds[NUM_LEDS-(int)end1-1] += CHSV(hue, 255, brightness*(1 - (end1 - (long)end1)));

	for (int i = end1 + 1; i < end2-1; i++) {
		leds[i] += CHSV(hue, 255, brightness);
		//leds[NUM_LEDS-i-1] += CHSV(hue, 255, brightness);
	}

	leds[(int)end2] += CHSV(hue, 255, brightness*(end2 - (long)end2));
	//leds[NUM_LEDS-(int)end2-1] += CHSV(hue, 255, brightness*(end2 - (long)end2));

}


