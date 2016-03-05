
#include "IRSensorsTest.h"

void IRSensorsTestClass::init()
{
  init_whiteline_array();
}

void IRSensorsTestClass::loop()
{
  get_keyence_array(sensorValues);
  omronValue = get_omron();

  Serial.print("Reading: \n");
  Serial.print("Keyence left: \n");
  Serial.print(sensorValues[0]);
  Serial.print("Keyence center: \n");
  Serial.print(sensorValues[1]);
  Serial.print("Keyence right: \n");
  Serial.print(sensorValues[2]);
  Serial.print("Omron: \n");
  Serial.print(omronValue);
}
IRSensorsTestClass IRSensorsTest;

