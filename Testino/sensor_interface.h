#ifndef _SENSOR_INTERFACE_h
#define _SENSOR_INTERFACE_h

#include "arduino.h"

#define WHITELINE_FRONT_LEFT_PIN    A0
#define WHITELINE_FRONT_RIGHT_PIN   A1
#define WHITELINE_REAR_LEFT_PIN     A2
#define WHITELINE_REAR_RIGHT_PIN    A3
#define KEYENCE_LEFT_PIN            9U		// D9
#define KEYENCE_CENTER_PIN          10U		// D10
#define KEYENCE_RIGHT_PIN           11U		// D11
#define OMRON_PIN                   14U		// MISO

#define KEYENCE_LEFT    0
#define KEYENCE_CENTER  1
#define KEYENCE_RIGHT   2

#define WHITELINE_FRONT_LEFT  0
#define WHITELINE_FRONT_RIGHT 1
#define WHITELINE_REAR_LEFT   2
#define WHITELINE_REAR_RIGHT  3

#define WHITELINE_MAX_TIMEOUT 2000		// Should change with tests
#define WHITELINE_THRESHOLD 500			// Should change with tests

void init_keyence_array();
void init_whiteline_array();
void init_omron();

void get_keyence_array(int* sensor_values);     // 3 elements-array
void get_whiteline_array(int* sensor_values);   // 4 elements-array
int get_omron();

// Reads the sensor values into an array. There *MUST* be space
// for as many values as there were sensors specified in the constructor.
// The values returned are in microseconds and range from 0 to MAX_TIMEOUT
void qtr_read(unsigned int *sensor_values);

#endif

