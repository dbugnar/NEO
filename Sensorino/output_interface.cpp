#include "output_interface.h"

void init_whiteline_code() 
{
	pinMode(WHITELINE_CODE_PIN0, OUTPUT);
	pinMode(WHITELINE_CODE_PIN1, OUTPUT);
	pinMode(WHITELINE_CODE_PIN2, OUTPUT);
}

void init_opponent_location()
{
	pinMode(OPPONENT_LOCATION_PIN0, OUTPUT);
	pinMode(OPPONENT_LOCATION_PIN1, OUTPUT);
}

void init_outgoing_interrupts()
{
	pinMode(INT_WHITELINE_PIN, OUTPUT);
	pinMode(INT_OPPONENT_SPOTTED_PIN, OUTPUT);
	pinMode(INT_OPPONENT_NEAR_PIN, OUTPUT);
}

void write_whiteline_code(int* whiteline_code_out)
{
	digitalWrite(WHITELINE_CODE_PIN0, whiteline_code_out[0]);
	digitalWrite(WHITELINE_CODE_PIN1, whiteline_code_out[1]);
	digitalWrite(WHITELINE_CODE_PIN2, whiteline_code_out[2]);
} 

void write_opponent_location(int* opponent_loc_out)
{
	digitalWrite(OPPONENT_LOCATION_PIN0, opponent_loc_out[0]);
	digitalWrite(OPPONENT_LOCATION_PIN1, opponent_loc_out[1]);
}

void write_outgoing_interrupts(int* outgoing_ints_out)
{
	digitalWrite(INT_WHITELINE_PIN, outgoing_ints_out[INT_WHITELINE]);
	digitalWrite(INT_OPPONENT_SPOTTED_PIN, outgoing_ints_out[INT_OPPONENT_SPOTTED]);
	digitalWrite(INT_OPPONENT_NEAR_PIN, outgoing_ints_out[INT_OPPONENT_NEAR]);
} 
