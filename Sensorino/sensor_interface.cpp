#include "sensor_interface.h"

void init_keyence_array()
{
	pinMode(KEYENCE_LEFT_PIN, INPUT);
	pinMode(KEYENCE_CENTER_PIN, INPUT);
	pinMode(KEYENCE_RIGHT_PIN, INPUT);
}

void init_omron()
{
	pinMode(OMRON_PIN, INPUT);
}

void init_whiteline_array()
{
	// Set pins to input and disable pullup
	pinMode(WHITELINE_FRONT_LEFT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_FRONT_LEFT_PIN, LOW);		// important: disable internal pull-up!

	pinMode(WHITELINE_FRONT_RIGHT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_FRONT_RIGHT_PIN, LOW);		// important: disable internal pull-up!

	pinMode(WHITELINE_REAR_LEFT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_REAR_LEFT_PIN, LOW);			// important: disable internal pull-up!

	pinMode(WHITELINE_REAR_RIGHT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_REAR_RIGHT_PIN, LOW);		// important: disable internal pull-up!
}

void get_keyence_array(int *sensor_values)
{
	sensor_values[KEYENCE_LEFT] = digitalRead(KEYENCE_LEFT_PIN);
	sensor_values[KEYENCE_CENTER] = digitalRead(KEYENCE_CENTER_PIN);
	sensor_values[KEYENCE_RIGHT] = digitalRead(KEYENCE_RIGHT_PIN);
}

int get_omron()
{
	return HIGH;
	//return digitalRead(OMRON_PIN);
}

void get_whiteline_array(int *sensor_values)
{
	qtr_read((unsigned int*)sensor_values);

	// Coerce the int values returned by qtr_read to a HIGH/LOW domain by using a experimental threshold.
	sensor_values[WHITELINE_FRONT_LEFT] = (unsigned int)sensor_values[WHITELINE_FRONT_LEFT] < WHITELINE_THRESHOLD ? HIGH : LOW;
	sensor_values[WHITELINE_FRONT_RIGHT] = (unsigned int)sensor_values[WHITELINE_FRONT_RIGHT] < WHITELINE_THRESHOLD ? HIGH : LOW;
	sensor_values[WHITELINE_REAR_LEFT] = (unsigned int)sensor_values[WHITELINE_REAR_LEFT] < WHITELINE_THRESHOLD ? HIGH : LOW;
	sensor_values[WHITELINE_REAR_RIGHT] = (unsigned int)sensor_values[WHITELINE_REAR_RIGHT] < WHITELINE_THRESHOLD ? HIGH : LOW;
}

void qtr_read(unsigned int *sensor_values)
{
	// Set pins to output and enable internal pullup
	sensor_values[WHITELINE_FRONT_LEFT] = WHITELINE_MAX_TIMEOUT;
	digitalWrite(WHITELINE_FRONT_LEFT_PIN, HIGH);		// make sensor line an output
	pinMode(WHITELINE_FRONT_LEFT_PIN, OUTPUT);			// drive sensor line high
	
	sensor_values[WHITELINE_FRONT_RIGHT] = WHITELINE_MAX_TIMEOUT;
	digitalWrite(WHITELINE_FRONT_RIGHT_PIN, HIGH);		// make sensor line an output
	pinMode(WHITELINE_FRONT_RIGHT_PIN, OUTPUT);			// drive sensor line high

	sensor_values[WHITELINE_REAR_LEFT] = WHITELINE_MAX_TIMEOUT;
	digitalWrite(WHITELINE_REAR_LEFT_PIN, HIGH);		// make sensor line an output
	pinMode(WHITELINE_REAR_LEFT_PIN, OUTPUT);			// drive sensor line high

	sensor_values[WHITELINE_REAR_RIGHT] = WHITELINE_MAX_TIMEOUT;
	digitalWrite(WHITELINE_REAR_RIGHT_PIN, HIGH);		// make sensor line an output
	pinMode(WHITELINE_REAR_RIGHT_PIN, OUTPUT);			// drive sensor line high

	// Charge lines for 10 us
	delayMicroseconds(10);              

	// Set pins to input and disable pullup
	pinMode(WHITELINE_FRONT_LEFT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_FRONT_LEFT_PIN, LOW);		// important: disable internal pull-up!

	pinMode(WHITELINE_FRONT_RIGHT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_FRONT_RIGHT_PIN, LOW);		// important: disable internal pull-up!

	pinMode(WHITELINE_REAR_LEFT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_REAR_LEFT_PIN, LOW);			// important: disable internal pull-up!

	pinMode(WHITELINE_REAR_RIGHT_PIN, INPUT);			// make sensor line an input
	digitalWrite(WHITELINE_REAR_RIGHT_PIN, LOW);		// important: disable internal pull-up!

	unsigned long startTime = micros();
	while (micros() - startTime < WHITELINE_MAX_TIMEOUT)
	{
		unsigned int time = micros() - startTime;
		
		// Check if the sensor capacitor has discharged and set the value of the sensors
		if (digitalRead(WHITELINE_FRONT_LEFT_PIN) == LOW && time < sensor_values[WHITELINE_FRONT_LEFT])
			sensor_values[WHITELINE_FRONT_LEFT] = time;

		if (digitalRead(WHITELINE_FRONT_RIGHT_PIN) == LOW && time < sensor_values[WHITELINE_FRONT_RIGHT])
			sensor_values[WHITELINE_FRONT_RIGHT] = time;

		if (digitalRead(WHITELINE_REAR_LEFT_PIN) == LOW && time < sensor_values[WHITELINE_REAR_LEFT])
			sensor_values[WHITELINE_REAR_LEFT] = time;

		if (digitalRead(WHITELINE_REAR_RIGHT_PIN) == LOW && time < sensor_values[WHITELINE_REAR_RIGHT])
			sensor_values[WHITELINE_REAR_RIGHT] = time;
	}
}
