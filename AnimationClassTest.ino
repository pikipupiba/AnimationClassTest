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
const int NUM_LEDS = 300;

struct CRGB leds[NUM_LEDS];//Initialization Code

/*
Animation *animation2 = new Animation(160, 0, 255, 31, 60);
Animation *animation3 = new Animation(2, 0, 255, 61, 90);
Animation *animation4 = new Animation(160, 0, 255, 91, 120);
Animation *animation5 = new Animation(2, 0, 255, 121, 150);
*/
const int numAnimations = 10;
Animation* animation[numAnimations];

// List of patterns to cycle through.  Each is defined as a separate function below.

typedef void(*SimplePatternList[])(uint8_t segments, uint8_t numColors, uint8_t hueSpeed);
SimplePatternList gPatterns = { GummyWorm1 , GummyWorm2 , GummyWorm3, GummyWorm4 };

uint8_t gCurrentPatternNumber = 0; // Index number of which pattern is current

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

	GummyWorm1(10, 5,2);
}

void loop(){

	EVERY_N_SECONDS(10) {

		nextPattern();

		for (int i = 0; i < numAnimations; i++) {
			if (animation[i] == NULL) {
			}
			else {
				delete animation[i];
				animation[i] = NULL;
			}
		}

		fadeToBlackBy(leds, NUM_LEDS, 255);


		gPatterns[gCurrentPatternNumber](10, 2, 1);

		Serial.println(freeMemory());
		Serial.println(gCurrentPatternNumber);
	}

	if (random8(0, 255) < 6) {
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

	//animation[0]->Display();

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

void GummyWorm1(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	//Serial.println("Gummy Worm 1 Start");

	segments = 5;

	uint16_t border[numAnimations+1];

	animation[0] = new Mover(5,1.6,5,true);
	animation[1] = new Mover(295, -1.6, 5, true);
	animation[2] = new Mover(100, 1.6, 5, true);
	animation[3] = new Mover(200, -1.6, 5, true);
	animation[4] = new Twinkle(100, 20);

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	for (int i = 0; i < segments; i++) {
		//animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

	//Serial.println("Gummy Worm 1 End");
}

void GummyWorm2(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	//Serial.println("Gummy Worm 2 Start");

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

	//Serial.println("Gummy Worm 3 Start");

	segments = 2;

	uint16_t border[numAnimations + 1];

	animation[0] = new Strobe(10,200);
	animation[1] = new Twinkle (50,20);
	//animation[2] = new Strobe(10, 200);
	//animation[3] = new Twinkle(50, 20);

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

}

void GummyWorm4(uint8_t segments, uint8_t numColors, uint8_t hueSpeed) {

	//Serial.println("Gummy Worm 4 Start");

	segments = 4;

	uint16_t border[numAnimations + 1];

	for (int i = 0; i < segments + 1; i++) {
		border[i] = i*(((NUM_LEDS) / segments));
	}

	animation[0] = new Strobe(50,100);
	animation[1] = new Strobe(25, 150);
	animation[2] = new Strobe(10, 50);
	animation[3] = new Strobe(1, 10);

	for (int i = 0; i < segments; i++) {
		animation[i]->SetRange(border[i] + 1, border[i + 1]);
		animation[i]->SetHue(i*(255 / numColors));
	}

	//Serial.println("Gummy Worm 4 End");

}