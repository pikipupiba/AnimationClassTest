/*
    Name:       AnimationClassTest.ino
    Created:	8/5/2018 11:12:26 PM
    Author:     DESKTOP-EE50DD5\pikip
*/
#include "Shutters.h"
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

//#define ARRAY_SIZE(a)                               \
//  ((sizeof(a) / sizeof(*(a))) /                     \
//  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

const uint8_t FRAMES_PER_SECOND = 120;
const int NUM_LEDS = 300;

//Initialization Code
struct CRGB leds[NUM_LEDS];
const uint8_t numAnimations = 10;
uint8_t curNumAnimations;
Animation* animation[numAnimations];

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void(*PatternList[])(uint8_t preset);
typedef void(*UpdateList[])(uint8_t preset);

PatternList gPatterns = { DancingSisters, ColorWipe, ShutterWipe };
UpdateList gUpdates = { UpdateDancingSisters, UpdateColorWipe, UpdateShutterWipe };

uint8_t gCurrentPatternNumber = 2; // Index number of which pattern is current
bool autoLoop = false;
bool trigger = true;

void setup(){

	Serial.begin(57600);
	delay(1000);
	pinMode(DATA_PIN, OUTPUT);
	// LED_TYPE,DATA_PIN,CLK_PIN,COLOR_ORDER
	LEDS.addLeds<LED_TYPE, DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS);
	FastLED.setBrightness(255);

	Serial.println("Starting...");
	Serial.println(freeMemory());
	Serial.print("Current Pattern: ");
	Serial.println(gCurrentPatternNumber);

	gPatterns[gCurrentPatternNumber](0);
}

void loop(){

	if (autoLoop) {
		EVERY_N_SECONDS(10) {
		Serial.println(freeMemory());
		
			Serial.println(freeMemory());
			nextPattern();
			Serial.println(freeMemory());
			for (int i = 0; i < numAnimations; i++) {
				if (animation[i] == NULL) {
				}
				else {
					delete animation[i];
					animation[i] = NULL;
				}
			}
			Serial.println(freeMemory());
			fadeToBlackBy(leds, NUM_LEDS, 255);
			Serial.println(freeMemory());
			gPatterns[gCurrentPatternNumber](0);

			Serial.println(freeMemory());
			Serial.println(gCurrentPatternNumber);
		}
	}
	
	/*EVERY_N_SECONDS(10) {
		trigger = !trigger;
	}*/

	gUpdates[gCurrentPatternNumber](0);

	//Serial.println("Before Update");
	for (int i = 0; i < numAnimations; i++) {
		if (animation[i] == NULL) {
		}
		else{
			animation[i]->Update();
		}
	}
	//Serial.println("After Update");

	// send the 'leds' array out to the actual LED strip
	FastLED.show();
	// insert a delay to keep the framerate modest
	FastLED.delay(1000 / FRAMES_PER_SECOND);

	

}

void nextPattern()
{
	// add one to the current pattern number, and wrap around at the end
	gCurrentPatternNumber = (gCurrentPatternNumber + 1) % 2; // ARRAY_SIZE(gPatterns);

}

void DancingSisters(uint8_t preset) {

	uint8_t numMovers = 2;
	uint8_t numColors = 5;

	uint16_t border[numAnimations+1];

	animation[0] = new Mover(240,0.2,10,true);
	//animation[0]->SetRange(20, 50);
	animation[1] = new Mover(40, 1.4, 10, true);
	//animation[2] = new Mover(160, 0.7, 10, true);
	//animation[3] = new Mover(120, 1.4, 10, true);
	animation[4] = new Twinkle(10, 30);
	//animation[5] = new Shutters(20, 1);
	Serial.println(freeMemory());

	for (int i = 0; i < numMovers + 1; i++) {
		border[i] = i*(((NUM_LEDS) / numMovers));
	}

	for (int i = 0; i < numMovers; i++) {
		//animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void UpdateDancingSisters(uint8_t preset) {

	 animation[0]->WobbleSize(1,  10, 11,  2, 10, 9,  1, 5,  17, 1, 8, 20);
	 animation[1]->WobbleSize(1,  5,  10,  2, 20, 13, 1, 15, 13, 1, 7, 21);
	 //animation[2]->WobbleSize(1,  5,   7,  2, 5 , 3 , 1, 10, 11, 1, 6, 18);
	 //animation[3]->WobbleSize(1,  10,  9,  2, 10, 13, 1, 12, 12, 1, 5, 15);

	animation[0]->WobbleSpeed(20, 50,   8, 5, 50, 10, 5, 50, 17, 5, 50, 20);
	animation[1]->WobbleSpeed(10, 60,  10, 5, 50, 13, 5, 50, 17, 5, 50, 17);
	//animation[2]->WobbleSpeed(10, 30,   7, 5, 50, 13, 5, 50, 17, 5, 50, 19);
	//animation[3]->WobbleSpeed(10, 100, 11, 5, 50, 13, 5, 50, 17, 5, 50, 18);

	for (int i = 0; i < 2; i++) {
		if (random8() < 4) {
			animation[i]->Bounce();
		}
	}
}

void ColorWipe(uint8_t preset) {

	animation[0] = new Mover(0, 0, 3, false);
	animation[1] = new Mover(NUM_LEDS / 2, 0, NUM_LEDS-3, false);
	animation[0]->SetHue(0);
	animation[0]->SetHue(120);

}

void UpdateColorWipe(uint8_t preset) {

	if (trigger) {
		animation[0]->Grow(1);
		animation[1]->Shrink(1);
	}
	else {
		animation[1]->Grow(1);
		animation[0]->Shrink(1);
	}

}

void ShutterWipe(uint8_t preset) {

	//animation[0] = new Shutters(30,0.5,0,0);
	//animation[1] = new Shutters(20, 1, 0,1);
	//animation[1]->SetHue(100);
	animation[2] = new Shutters(16, 1.5, 0, 1);
	animation[2]->SetHue(200);

	//animation[1] = new Twinkle(10, 30);

}

void UpdateShutterWipe(uint8_t preset) {
	//float newSpeed = (float)(beatsin8(10, 2, 30) + beatsin8(4, 2, 70) + beatsin8(13, 2, 20) + beatsin8(19, 2, 20)) / 120;
	//animation[0]->SetSpeed(newSpeed);
	//animation[1]->SetSpeed(newSpeed);
}