#ifndef _WHITELINESENSORTEST_h
#define _WHITELINESENSORTEST_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "../Sensorino/sensor_interface.h"

class IRSensorsSensorTestClass: public FuriosityTest
{
 public:
  virtual void init();
  virtual void loop();
  int sensorValues[3];
  int omronValue;
};

extern IRSensorsTestClass IRSensorsTest;

#endif

