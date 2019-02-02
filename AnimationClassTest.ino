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

#define ARRAY_SIZE(a)                               \
  ((sizeof(a) / sizeof(*(a))) /                     \
  static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

const uint8_t FRAMES_PER_SECOND = 60;
const int NUM_LEDS = 235;

//Initialization Code
struct CRGB leds[NUM_LEDS];
const uint8_t numAnimations = 10;
uint8_t curNumAnimations;
Animation* animation[numAnimations];

// List of patterns to cycle through.  Each is defined as a separate function below.
typedef void(*PatternList[])(uint8_t preset);
typedef void(*UpdateList[])(uint8_t preset);

PatternList gPatterns = { DancingSisters,ColorWipe };
UpdateList gUpdates = { UpdateDancingSisters,UpdateColorWipe };

uint8_t gCurrentPatternNumber = 1; // Index number of which pattern is current
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
	
	EVERY_N_SECONDS(10) {
		trigger = !trigger;
	}

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
	gCurrentPatternNumber = (gCurrentPatternNumber + 1) % ARRAY_SIZE(gPatterns);

}

void DancingSisters(uint8_t preset) {

	uint8_t numMovers = 1;
	uint8_t numColors = 5;

	uint16_t border[numAnimations+1];

	animation[0] = new Mover(10,0.5,10,false);
	//animation[0]->SetRange(20, 50);
	//animation[1] = new Mover(0, 1.4, 10, false);
	//animation[2] = new Mover(120, 0.7, 10, false);
	//animation[3] = new Mover(120, 1.4, 10, false);
	//animation[4] = new Twinkle(5, 10);

	for (int i = 0; i < numMovers + 1; i++) {
		border[i] = i*(((NUM_LEDS) / numMovers));
	}

	for (int i = 0; i < numMovers; i++) {
		//animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void UpdateDancingSisters(uint8_t preset) {



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