#ifndef SENSOR_INTERFACE
#define SENSOR_INTERFACE

#define WHITELINE_FRONT_LEFT_PIN	A0
#define WHITELINE_FRONT_RIGHT_PIN	A1
#define WHITELINE_REAR_LEFT_PIN		A2
#define WHITELINE_REAR_RIGHT_PIN	A3
#define KEYENCE_LEFT_PIN			D9
#define KEYENCE_CENTER_PIN			D10
#define KEYENCE_RIGHT_PIN			D11
#define OMRON_PIN					MISO // Aici cred ca trbeuie dat exact numarul pinului

#define KEYENCE_LEFT 0
#define KEYENCE_CENTER 1
#define KEYENCE_RIGHT 2

#define NUM_WHITELINE_SENSORS 4
#define WHITELINE_FRONT_LEFT 0
#define WHITELINE_FRONT_RIGHT 1
#define WHITELINE_REAR_LEFT 2
#define WHITELINE_REAR_RIGHT 3

#define WHITELINE_DISTANCE 2 	// 2mm? - schimba aici daca nu e in mm


void init_keyence_array();
void init_whiteline_array();	// daca trebuie si distanta, foloseste definitia din fisierul asta
void init_omron();

int[3] get_keyence_array();	// in cazul in care trebuie trimisi si pinii ca argument, sa schimbi linistit
unsigned int[NUM_WHITELIEN_SENSORS] get_whiteline_array();
int get_omron();

#endif
