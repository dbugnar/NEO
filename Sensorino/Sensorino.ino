#include "output_interface.h"
#include "sensor_interface.h"

int keyence_reading[3];     
int whiteline_reading[4];   
int omron_reading;

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
	/* Whiteline code:
	*
	*  000: Front		 100: Back
	*  001: FrontRight   101: BackLeft
	*  010: FrontLeft    110: BackRight
	*  011: Left		 111: Right
	*/
	// WL_CODE[0] is computed as: (rl AND NOT(rr)) OR (NOT(fl) AND fr)
	whiteline_code[0] = (whiteline_reading[WHITELINE_REAR_LEFT] & (1 - whiteline_reading[WHITELINE_REAR_RIGHT])) |
		((1 - whiteline_reading[WHITELINE_FRONT_LEFT]) & whiteline_reading[WHITELINE_FRONT_RIGHT]);

	// WL_CODE[1] is computed as: (NOT(rl) AND rr) OR (fl AND NOT(fr))
	whiteline_code[1] = ((1 - whiteline_reading[WHITELINE_REAR_LEFT]) & whiteline_reading[WHITELINE_REAR_RIGHT]) |
		(whiteline_reading[WHITELINE_FRONT_LEFT] & (1 - whiteline_reading[WHITELINE_FRONT_RIGHT]));

	// WL_CODE[2] is computed as: (NOT(fr) AND NOT(rr)) OR (NOT(rl) AND rr)
	whiteline_code[2] = ((1 - whiteline_reading[WHITELINE_FRONT_RIGHT]) & (1 - whiteline_reading[WHITELINE_REAR_RIGHT])) |
		((1 - whiteline_reading[WHITELINE_REAR_LEFT]) & whiteline_reading[WHITELINE_REAR_RIGHT]);

	/* Opponent location code:
	*
	*  00: Center Mid
	*  01: Center - This is augmented with the omron sensor reading to determine if the opponent is near
	*  10: Left Far
	*  11: Right Far
	*/
	// OP_LOC[0] is computed as: NOT((left OR right) AND (center OR right))
	opponent_location_code[0] = 1 - ((keyence_reading[KEYENCE_LEFT] | keyence_reading[KEYENCE_RIGHT]) &
		(keyence_reading[KEYENCE_CENTER] | keyence_reading[KEYENCE_RIGHT]));
	// OP_LOC[1] is computed as: NOT(center)
	opponent_location_code[1] = 1 - keyence_reading[KEYENCE_CENTER];

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


	/********************Wrtite to control interface********************/
	write_whiteline_code(whiteline_code);
	write_opponent_location(opponent_location_code);
	write_outgoing_interrupts(outgoing_interrupts);
}
