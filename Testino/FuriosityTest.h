#ifndef _FURIOSITYTEST_h
#define _FURIOSITYTEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class FuriosityTest
{
 public:
	virtual void init() =0;
	virtual void loop() =0;

	void init_output_pins(int* pins, int pin_count);
	void init_input_pins(int* pins, int pin_count);
};

#endif

