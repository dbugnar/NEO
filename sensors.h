#ifndef SENSOR_INTERFACE
#define SENSOR_INTERFACE

#define KEYENCE_LEFT 0
#define KEYENCE_CENTER 1
#define KEYENCE_RIGHT 2

#define NUM_WHITELINE_SENSORS 4
#define WHITELINE_FRONT_LEFT A0
#define WHITELINE_FRONT_RIGHT A1
#define WHITELINE_REAR_LEFT A2
#define WHITELINE_REAR_RIGHT A3

#define WHITELINE_DISTANCE 2 	// 2mm? - schimba aici daca nu e in mm


void init_keyence_array(int[3] pins);
void init_whiteline_aray(int[4] pins);	// daca trebuie si distanta, foloseste definitia din fisierul asta
void init_omron(int pin);

int[3] get_keyence_array();	// in cazul in care trebuie trimisi si pinii ca argument, sa schimbi linistit
unsigned int[4] get_whiteline_array();
int get_omron();

#endif
