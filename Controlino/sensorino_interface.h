#ifndef _SENSORINO_INTERFACE_h
#define _SENSORINO_INTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define OPLOC_FAR_LEFT 0
#define OPLOC_FAR_RIGHT 1
#define OPLOC_CENTER 2
#define OPLOC_CENTER_MID 3

#define	START_PIN	10	//pin 10 sau pe cat punem start-stop
#define OPPONENT_LOCATION_PIN0		8 //pin 8
#define OPPONENT_LOCATION_PIN1		9 //pin 9
#define INT_OPPONENT_SPOTTED_PIN	7 //pin 7

void init_opponent_location();
void init_opponent_spotted();
void init_start_signal();

int read_opponent_location();
int read_opponent_spotted();
int read_start_signal();

#endif

