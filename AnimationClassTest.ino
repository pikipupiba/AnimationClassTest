/*
    Name:       AnimationClassTest.ino
    Created:	8/5/2018 11:12:26 PM
    Author:     DESKTOP-EE50DD5\pikip
*/
#include <FastLED.h>
#include "Animation.h"
#include "Mover.h"
#include "Strobe.h"
#include "Twinkle.h"
#include <MemoryFree.h>

#if FASTLED_VERSION < 3001000
#error "Requires FastLED 3.1 or later; check github for latest code."
#endif

// Fixed definitions cannot change on the fly.
#define DATA_PIN      12
#define COLOR_ORDER   GRB
#define LED_TYPE      WS2812B

const uint8_t FRAMES_PER_SECOND = 60;
const int NUM_LEDS = 300;

struct CRGB leds[NUM_LEDS];//Initialization Code

/*
Animation *animation2 = new Animation(160, 0, 255, 31, 60);
Animation *animation3 = new Animation(2, 0, 255, 61, 90);
Animation *animation4 = new Animation(160, 0, 255, 91, 120);
Animation *animation5 = new Animation(2, 0, 255, 121, 150);
*/
const int numAnimations = 10;
Mover *animation[numAnimations];

void setup(){

	Serial.begin(57600);
	delay(1000);
	pinMode(DATA_PIN, OUTPUT);
	// LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER
	LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);

	GummyWorm1(10, 2,2);
}

// List of patterns to cycle through.  Each is defined as a separate function below.

typedef void(*SimplePatternList[])(uint8_t segments, uint8_t numColors, uint8_t hueSpeed);
SimplePatternList gPatterns = { GummyWorm1 , GummyWorm2 , GummyWorm3, GummyWorm4};

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

void loop(){

	/*EVERY_N_SECONDS(10) {

		nextPattern();

		Serial.println(freeMemory());

		for (int i = 0; i < numAnimations; i++) {
			delete animation[i];
		}

		fadeToBlackBy(leds, NUM_LEDS, 255);


		gPatterns[gCurrentPatternNumber](random8(2, 20), random8(2, 5), random8(1, 3));
	}*/

	
	if (random8(0, 255) < 5) {
		animation[0]->Bounce();
	}

	for (int i = 0; i < numAnimations; i++) {
		if (animation[i] == NULL) {
		}
		else{
			animation[i]->SetSpeed(float(beatsin8(11,5,50)+ beatsin8(4, 5, 50)+ beatsin8(3, 5, 50) + beatsin8(7, 5, 50))/70);
			animation[i]->Update();
		}
	}

	animation[0]->Display();

	// send the 'leds' array out to the actual LED strip
	//FastLED.show();
	// insert a delay to keep the framerate modest
	//FastLED.delay(1000 / FRAMES_PER_SECOND);

	

}

void nextPattern()
{
	// add one to the current pattern number, and wrap around at the end
	gCurrentPatternNumber = (gCurrentPatternNumber + 1) % 4;//(ARRAY_SIZE(gPatterns) - 1);

}

void GummyWorm1(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	segments = 1;

	uint16_t border[numAnimations+1];

	for (int i = 0; i < segments; i++) {
		//animation[i] = new Animation(i*(255/numColors),hueSpeed,128);
		animation[i] = new Mover(5,1.6,5,true);
	}

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void GummyWorm2(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	segments = numAnimations;

	uint16_t border[numAnimations + 1];


	animation[0] = new Mover(5, 1.6, 5, true);
	animation[1] = new Mover(5, 1.6, 5, true);
	animation[2] = new Mover(5, 1.6, 5, true);
	animation[3] = new Mover(5, 1.6, 5, true);
	animation[4] = new Mover(5, 1.6, 5, true);
	animation[5] = new Mover(295, -1.6, 5, true);
	animation[6] = new Mover(295, -1.6, 5, true);
	animation[7] = new Mover(295, -1.6, 5, true);
	animation[8] = new Mover(295, -1.6, 5, true);
	animation[9] = new Mover(295, -1.6, 5, true);
	

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void GummyWorm3(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	segments = numAnimations;

	uint16_t border[numAnimations + 1];


	animation[0] = new Mover(150, 1.6, 5, true);
	animation[1] = new Mover(150, 1.6, 5, true);
	animation[2] = new Mover(150, 1.6, 5, true);
	animation[3] = new Mover(150, 1.6, 5, true);
	animation[4] = new Mover(150, 1.6, 5, true);
	animation[5] = new Mover(150, -1.6, 5, true);
	animation[6] = new Mover(150, -1.6, 5, true);
	animation[7] = new Mover(150, -1.6, 5, true);
	animation[8] = new Mover(150, -1.6, 5, true);
	animation[9] = new Mover(150, -1.6, 5, true);


	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void GummyWorm4(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	segments = numAnimations;

	uint16_t border[numAnimations + 1];

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	animation[0] = new Mover(border[1], -1.6, 5, true);
	animation[1] = new Mover(border[1], 1.6, 5, true);
	animation[2] = new Mover(border[3], -1.6, 5, true);
	animation[3] = new Mover(border[3], 1.6, 5, true);
	animation[4] = new Mover(border[5],-1.6, 5, true);
	animation[5] = new Mover(border[5], 1.6, 5, true);
	animation[6] = new Mover(border[7], -1.6, 5, true);
	animation[7] = new Mover(border[7], 1.6, 5, true);
	animation[8] = new Mover(border[9], -1.6, 5, true);
	animation[9] = new Mover(border[9], 1.6, 5, true);


	

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}