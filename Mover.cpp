#include "Mover.h"

Mover::Mover(float newPosition, float newSpeed, float newSize, bool newBounce){
	
	position = newPosition;
	speed = newSpeed;
	size = newSize;
	bounce = newBounce;

	end1 = position - size / 2;
	end2 = position + size / 2;

	tailLength = size * 2 / 5;

	prevEnd1 = end1;
	prevEnd2 = end2;
	prevHue = hue;
	
	hue = 0;
	hueSpeed = 1;
	brightness = 255;
	rangeStart = 0;
	rangeEnd = NUM_LEDS-1;
	reflect = false;
	
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

void Mover::Grow(float amount)
{
	if (size + amount < rangeEnd - rangeStart) {
		size += amount;
	}
}

void Mover::Shrink(float amount)
{
	if (size - amount > 3) {
		size -= amount;
	}
}

void Mover::Bounce()
{
	speed = -speed;
}



void Mover::ErasePrevFrame(){

	leds[(int)prevEnd1] -= CHSV(prevHue, 255, brightness*(1 - (prevEnd1 - (long)prevEnd1)));
	
	if (end1 < end2) {
		for (int i = prevEnd1 + 1; i < prevEnd2 - 1; i++) {
			leds[i] -= CHSV(prevHue, 255, brightness);
		}
	}
	else {
		for (int i = prevEnd1 + 1; i <= rangeEnd; i++) {
			leds[i] -= CHSV(prevHue, 255, brightness);
		}
		for (int i = prevEnd2 - 1; i >= (int)rangeStart && prevEnd2 > 1; i--) {
			leds[i] -= CHSV(prevHue, 255, brightness);
		}
	}

	leds[(int)prevEnd2] -= CHSV(prevHue, 255, brightness*(prevEnd2 - (long)prevEnd2));

	if (reflect) {
		leds[NUM_LEDS - (int)prevEnd1 - 1] -= CHSV(prevHue, 255, brightness*(1 - (prevEnd1 - (long)prevEnd1)));
		for (int i = prevEnd1 + 1; i < prevEnd2 - 1; i++) {
			leds[NUM_LEDS - i - 1] -= CHSV(prevHue, 255, brightness);
		}
		leds[NUM_LEDS - (int)prevEnd2 - 1] -= CHSV(prevHue, 255, brightness*(prevEnd2 - (long)prevEnd2));
	}

}

void Mover::UpdatePosition() {

	if (bounce) {
		if (speed > 0 && end2 + speed > rangeEnd) {
			Bounce();
		}
		else if (speed < 0 && end1 + speed < rangeStart) {
			Bounce();
		}
	}

	position += speed;

	prevEnd1 = end1;
	prevEnd2 = end2;
	prevHue = hue;

	if (position > rangeEnd+1) {
		position = rangeStart+(position-(rangeEnd+1));
	}
	else if (position < rangeStart) {
		position = rangeEnd;
	}

	end1 = position - size / 2;
	end2 = position + size / 2;

	if (end1 < (int)rangeStart) {
		end1 = rangeEnd - (rangeStart - end1 - 1);
	}

	if (end2 > rangeEnd+1) {
		end2 = rangeStart + (end2 - rangeEnd - 1);
	}

	/*
	Serial.print("End1: ");
	Serial.print(end1);
	Serial.print("  Position: ");
	Serial.print(position);
	Serial.print("  End2: ");
	Serial.println(end2);
	*/

	hue += hueSpeed;

}

void Mover::Draw(){

	leds[(int)end1] += CHSV(hue, 255, brightness*(1-(end1 - (long)end1)));
	
	if (end1 < end2) {
		for (int i = end1 + 1; i < end2 - 1; i++) {
			leds[i] += CHSV(hue, 255, brightness);
		}
	}
	else {
		for (int i = end1 + 1; i <= rangeEnd; i++) {
			leds[i] += CHSV(hue, 255, brightness);
		}
		for (int i = end2 - 1; i >= (int)rangeStart && end2 > 1; i--) {
			leds[i] += CHSV(hue, 255, brightness);
		}
	}
	
	leds[(int)end2] += CHSV(hue, 255, brightness*(end2 - (long)end2));

	if (reflect) {
		leds[NUM_LEDS - (int)end1 - 1] += CHSV(hue, 255, brightness*(1 - (end1 - (long)end1)));

		for (int i = end1 + 1; i < end2 - 1; i++) {
			leds[NUM_LEDS - i - 1] += CHSV(hue, 255, brightness);
		}
		leds[NUM_LEDS - (int)end2 - 1] += CHSV(hue, 255, brightness*(end2 - (long)end2));
	}
}


