#ifndef _WHITELINESENSORTEST_h
#define _WHITELINESENSORTEST_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#include "../Sensorino/sensor_interface.h"

class WhitelineSensorTestClass: public FuriosityTest
{
 public:
	virtual void init();
	virtual void loop();
};

extern WhitelineSensorTestClass WhitelineSensorTest;

#endif

