#include "Animation.h"

//Animation Class Constructors

Animation::Animation(){
	hue = 0;
	hueSpeed = 0;
	brightness = 128;
	rangeStart = 0;
	rangeEnd = NUM_LEDS - 1;
	reflect = false;

	prevHue = hue;
}

Animation::Animation(uint8_t newHue, uint8_t newHueSpeed){
	hue = newHue;
	hueSpeed = newHueSpeed;
	brightness = 255;
	rangeStart = 0;
	rangeEnd = NUM_LEDS - 1;
	reflect = false;

	prevHue = hue;
}

Animation::Animation(uint8_t newHue, uint8_t newHueSpeed, uint8_t newBrightness){
	hue = newHue;
	hueSpeed = newHueSpeed;
	brightness = newBrightness;
	rangeStart = 0;
	rangeEnd = NUM_LEDS - 1;
	reflect = false;

	prevHue = hue;
}

Animation::Animation(uint8_t newHue, uint8_t newHueSpeed, uint8_t newBrightness, uint16_t newRangeStart, uint16_t newRangeEnd){
	hue = newHue;
	hueSpeed = newHueSpeed;
	brightness = newBrightness;
	rangeStart = newRangeStart;
	rangeEnd = newRangeEnd;
	reflect = false;

	prevHue = hue;
}

Animation::~Animation(){

}

//Animation Class Get Functions

//Animation Class Set Functions

void Animation::SetHue(uint8_t newHue){
	prevHue = hue;
	hue = newHue;
}

void Animation::SetHue(uint8_t newHue, uint8_t newHueSpeed){
	prevHue = hue;
	hue = newHue;
	hueSpeed = newHueSpeed;
}

void Animation::SetBrightness(uint8_t newBrightness){
	brightness = newBrightness;
}

void Animation::SetRange(uint16_t newRangeStart, uint16_t newRangeEnd){
	rangeStart = newRangeStart;
	rangeEnd = newRangeEnd;
}

//Animation Class Utility Functions

void Animation::Update(){
	for (int i = rangeStart; i <= rangeEnd; i++) {
		leds[i] = CHSV(hue, 255, brightness);
		//leds[NUM_LEDS-i-1] = CHSV(hue, 255, brightness);
	}
	hue += hueSpeed;
}

void Animation::Display(){
	// send the 'leds' array out to the actual LED strip
	FastLED.show();
	// insert a delay to keep the framerate modest
	FastLED.delay(1000 / FRAMES_PER_SECOND);

	//fadeToBlackBy(leds, NUM_LEDS, 255);
}

void Animation::SetSpeed(float newSpeed)
{
}

void Animation::Bounce()
{
}


