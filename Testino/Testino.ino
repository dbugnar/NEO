#include "WhitelineSensorTest.h"
#include "IRSensorsTest.h"
#include "InterruptsTest.h'
#include "FuriosityTest.h"

void setup() {
	IRSensors.init();
}

void loop() {
	IRSensorsTest.loop();
}
