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

int init_opponent_location();
int init_opponent_spotted();
void init_start_signal();

int read_opponent_location();
int read_opponent_spotted();
int read_start_signal();

#endif

