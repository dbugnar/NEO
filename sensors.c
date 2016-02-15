#include <QRTSensors.h>
#define NUM_WHITELINE_SENSORS 4

QRTSensorsRC white_line_sensors((unsigned char []) {A0, A1, A2, A3}, NUM_WHITELINE_SENSORS)
unsigned int white_line_values[NUM_WHITELINE_SENSORS];

unsigned int[NUM_WHITELINE_SENSORS] get_whiteline_array()
{
	return white_line_values;
}

void setup() 
{
	//Just want to test this calibrate method 
	for (int i = 0; i < 400; i++)
		white_line_sensors.calibrate();
}

void loop()
{
	white_line_sensors.read(white_line_values);
}
