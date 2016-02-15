#include <QRTSensors.h>
#define NUM_WHITELINE_SENSORS 4
#define NUM_KEYENCE_SENSORS 4

QRTSensorsRC white_line_sensors((unsigned char []) {A0, A1, A2, A3}, NUM_WHITELINE_SENSORS);
unsigned int white_line_values[NUM_WHITELINE_SENSORS];
int keyence_values[NUM_KEYENCE_SENSORS];

void init_keyence_array()
{
	pinMode(KEYENCE_LEFT_PIN, OUTPUT);
	pinMode(KEYENCE_CENTER_PIN, OUTPUT);
	pinMode(KEYENCE_RIGHT_PIN, OUTPUT);
}

void init_omron_array()
{
	pinMode(OMRON_PIN, OUTPUT);
}

void init_whiteline_array()
{
	//Just want to test this calibrate method 
	for (int i = 0; i < 400; i++)
		white_line_sensors.calibrate();
}

int[NUM_KEYENCE_SENSORS] get_keyence_array()
{
	return keyence_values;
}

int get_omron()
{
	return digitalRead(OMRON_PIN);
}

unsigned int[NUM_WHITELINE_SENSORS] get_whiteline_array()
{
	white_line_sensors.read(white_line_values);
	return white_line_values;
}
