#include "output_interface.h"
#include "sensor_interface.h"

// (FL * 8) + (FR * 4) + (RL * 2) + RR
const int whiteline_code_LUT0[16] = { 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
const int whiteline_code_LUT1[16] = { 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0 };
const int whiteline_code_LUT2[16] = { 0, 0, 1, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 };

// (L * 4) + (C * 2) + R
const int opponent_location_LUT0[8] = { 0, 1, 0, 0, 1, 0, 0, 0 };
const int opponent_location_LUT1[8] = { 0, 0, 1, 0, 1, 0, 0, 0 };

int keyence_reading[3];     
int whiteline_reading[4];   
int omron_reading = HIGH;

int whiteline_code[3];          
int opponent_location_code[2];  
int outgoing_interrupts[3];     

void setup() {
	init_keyence_array();
	init_whiteline_array();
	init_omron();

	init_whiteline_code();
	init_opponent_location();
	init_outgoing_interrupts();
}

void loop() {
	/************************Get sensor data****************************/
	get_keyence_array(keyence_reading);
	get_whiteline_array(whiteline_reading);
	omron_reading = get_omron();

	/*********************Compute control codes*************************/
	/* Whiteline code (W0|W1|W2):
	* 
	*  000: Front		 100: Back
	*  001: FrontRight   101: BackLeft
	*  010: FrontLeft    110: BackRight
	*  011: Left		 111: Right
	*/
	int wl_index, opploc_index;

	wl_index = (whiteline_reading[WHITELINE_FRONT_LEFT] << 3) + (whiteline_reading[WHITELINE_FRONT_RIGHT] << 2) + (whiteline_reading[WHITELINE_REAR_LEFT] << 1) + whiteline_reading[WHITELINE_REAR_RIGHT];
	whiteline_code[0] = whiteline_code_LUT0[wl_index];
	whiteline_code[1] = whiteline_code_LUT1[wl_index];
	whiteline_code[2] = whiteline_code_LUT2[wl_index];

	/* Opponent location code (L0|L1):
	*
	*  00: Center Mid
	*  01: Center - This is augmented with the omron sensor reading to determine if the opponent is near
	*  10: Left Far
	*  11: Right Far
	*/

	opploc_index = (keyence_reading[KEYENCE_LEFT] << 2) + (keyence_reading[KEYENCE_CENTER] << 1) + keyence_reading[KEYENCE_RIGHT];
	opponent_location_code[0] = opponent_location_LUT0[opploc_index];
	opponent_location_code[1] = opponent_location_LUT1[opploc_index];

	/* Outgoing interrupts:
	*
	* INT_WHITELINE = Logical OR between whiteline sensor readings
	* INT_OPPONENT_SPOTTED = Logical OR between keyence sensor readings
	* INT_OPPONENT_NEAR = Logical AND between omron sensor reading and OpponentLocationCode == 00 (Center Mid)
	*/
	outgoing_interrupts[INT_WHITELINE] = whiteline_reading[WHITELINE_FRONT_LEFT] | whiteline_reading[WHITELINE_FRONT_RIGHT] |
		whiteline_reading[WHITELINE_REAR_LEFT] | whiteline_reading[WHITELINE_REAR_RIGHT];
	outgoing_interrupts[INT_OPPONENT_SPOTTED] = keyence_reading[KEYENCE_LEFT] | keyence_reading[KEYENCE_CENTER] | keyence_reading[KEYENCE_RIGHT];
	outgoing_interrupts[INT_OPPONENT_NEAR] = (1 - opponent_location_code[0]) & (1 - opponent_location_code[1]) & omron_reading;


	/********************Write to control interface********************/
	write_whiteline_code(whiteline_code);
	write_opponent_location(opponent_location_code);
	write_outgoing_interrupts(outgoing_interrupts);
}
