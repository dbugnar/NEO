// control_interface.h

#ifndef _CONTROL_INTERFACE_h
#define _CONTROL_INTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DIR_CONTROL_OFFSET 1
#define CENTER_CONTROL_OFFSET 20
#define MAX_SPEED 20
#define DONT_MOVE 0

void writeMotors(int a, int b);


#endif

