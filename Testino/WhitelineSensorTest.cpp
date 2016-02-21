// 
// 
// 

#include "WhitelineSensorTest.h"

void WhitelineSensorTestClass::init()
{
	init_whiteline_array();
}

void WhitelineSensorTestClass::loop()
{
	int reading[4];
	get_whiteline_array(reading);

	Serial.print("Reading: ");
	Serial.print(reading[0]);
	Serial.print(reading[1]);
	Serial.print(reading[2]);
	Serial.print(reading[3]);
}

WhitelineSensorTestClass WhitelineSensorTest;

