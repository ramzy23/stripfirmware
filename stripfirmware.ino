#include <FastLED.h>
#include <EEPROM.h>
#include "definitions.h";
#include "memory.h";


#define NUM_LEDS 12
#define DATA_PIN 7

CRGB leds[NUM_LEDS];

//---------------------------------------Notes---------------------------------------//
/*

	By using the colour method with NUM_LEDS, you will set all LEDS to the
	given colour



*/
//-----------------------------------------------------------------------------------//

//----------------------------Global variables----------------------------------//
int brightness = DEFAULT_BRIGHTNESS;
int current_colour = DEFAULT_COLOUR;
//-----------------------------------------------------------------------------------//
//-----------------------------------Startup Notes-----------------------------------//
/*
	1. Assign LED array with LEDS
	2. Turn off all LEDs!
	3. Wait to ensure everything is ready
	4. Fetch available stored data and assign it
	5. If not set all default values
*/
//-----------------------------------------------------------------------------------//

//--------------------------------Function Definitions-------------------------------//

void colour(int led = NUM_LEDS, int color = DEFAULT_COLOUR);
void setBrightness(int value = DEFAULT_BRIGHTNESS);
void fadeIn(int delayTime = DEFAULT_FADE_TIME);
void fadeOut(int delayTime = DEFAULT_FADE_TIME);
void breathe(int delayTime = DEFAULT_FADE_TIME);
void slideRight(int col = DEFAULT_COLOUR,int slideDelay = DEFAULT_SLIDE_DELAY);
void slideLeft(int col = DEFAULT_COLOUR,int slideDelay = DEFAULT_SLIDE_DELAY);
void eachRandomLed(int delayTime = DEFAULT_SLIDE_DELAY);
void switchColour(int delayTime = DEFAULT_SWITCH_DELAY,int color = randomColour());
void nightRider(int slideDelay = DEFAULT_SLIDE_DELAY);

//-----------------------------------------------------------------------------------//

void setup() {
	Serial.begin(9600);
	LEDS.addLeds<WS2812,DATA_PIN,RGB>(leds,NUM_LEDS);
	blank();
	delay(SAFETY_DELAY);
	setBrightness();
	colour();
}

void loop() {
	eachRandomLed();
}


//----------------------------Extra Functions-----------------------------------//

//This will turn off all the LEDS
void blank(){
	for (int i = 0; i < NUM_LEDS;i++){
		leds[i] = CRGB(0,0,0);
	}
	FastLED.show();
}

//This will make a specific LED the colour specified by the CRGB Colour object. If no colour is passed into the function then DEFAULT_COLOUR is set.
void colour(int led = NUM_LEDS, int color = DEFAULT_COLOUR){
	if (led == NUM_LEDS){
		for (int i = 0; i < NUM_LEDS; i++){
			colour(i,color);
		}
	}
	else{
	leds[led] = color;
	}
	FastLED.show();
}


/*	
	This will set the brightness of the strip. If no value is given the default 
	is sent.
*/
void setBrightness(int value = DEFAULT_BRIGHTNESS){
	FastLED.setBrightness(value);
	FastLED.show();
}


void studyMode(){
	colour(NUM_LEDS,WhiteSmoke);
}

//----------------------------------Fade Functions-----------------------------------//
/* 	These are the fading functions. These ensure that in any case the 
	function will fire

*/


void fadeIn(int delayTime = DEFAULT_FADE_TIME){
	for (int i = MINIMUM_BRIGHTNESS; i < MAXIMUM_BRIGHTNESS; i++){
		setBrightness(i);
		delay(DEFAULT_FADE_TIME);
	}
}

void fadeOut(int delayTime = DEFAULT_FADE_TIME){
	for (int i = MAXIMUM_BRIGHTNESS; i > MINIMUM_BRIGHTNESS; i--){
		setBrightness(i);
		delay(DEFAULT_FADE_TIME);
	}
}

void breathe(int delayTime = DEFAULT_FADE_TIME){
	setBrightness(MINIMUM_BRIGHTNESS);
	fadeIn(delayTime);
	setBrightness(MAXIMUM_BRIGHTNESS);
	fadeOut(delayTime);
	setBrightness(MINIMUM_BRIGHTNESS);
}

//------------------------------------------------------------------------------//

//----------------------------Solid Functions-----------------------------------//

/* 	
	These are the solid colour functions. 
*/

int randomColour(){
	randomSeed(micros()*analogRead(A1)*analogRead(A3));
	int seed = random8(142) * random16(142);
	while (seed > 141){
		if (seed < 0){
			seed = seed * -1;
		}
		seed = seed/random(8);
	}

	if (fullColourArray[seed] == current_colour){
		seed = random8(seed);
	}
	return fullColourArray[seed];
}

//-----------------------------------------------------------------------------------//

//------------------------------------Animations-------------------------------------//

void slideRight(int col = DEFAULT_COLOUR,int slideDelay = DEFAULT_SLIDE_DELAY){
	for (int i = 0; i < NUM_LEDS;i++){
		colour(i,col);
		delay(slideDelay);
	}
}

void slideLeft(int col = DEFAULT_COLOUR,int slideDelay = DEFAULT_SLIDE_DELAY){
	for (int i = 0; i < NUM_LEDS;i++){
		colour(NUM_LEDS - 1 - i,col);
		delay(slideDelay);
	}
}

void nightRider(int slideDelay = DEFAULT_SLIDE_DELAY){
	slideLeft(randomColour(),slideDelay);
	slideRight(randomColour(),slideDelay);
}

void eachRandomLed(int delayTime = DEFAULT_SLIDE_DELAY){
	for (int i = 0; i < NUM_LEDS; i ++){
		colour(i,randomColour());
		delay(delayTime);
	}
}

void switchColour(int delayTime = DEFAULT_SWITCH_DELAY,int color = randomColour()){
	colour(NUM_LEDS,color);
	delay(delayTime);
}

//-----------------------------------------------------------------------------------//
