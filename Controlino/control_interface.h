// control_interface.h

#ifndef _CONTROL_INTERFACE_h
#define _CONTROL_INTERFACE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

#define DIR_CONTROL_OFFSET 1
#define CENTER_CONTROL_OFFSET 20
#define MAX_SPEED 255
#define DONT_MOVE 0
//Motors
#define BUFFER_LENGTH 9
typedef struct
{
	uint8_t packetStart[3];
	int16_t pMotorR_sds16;
	int16_t pMotorL_sds16;
	int16_t yCheck_sds16;
} motorCommand;

typedef union
{
	motorCommand sMotorCommand;
	uint8_t data[BUFFER_LENGTH];
} rawPacket;


void writeMotors(int a, int b);

#endif


