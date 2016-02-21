#ifndef _OUTPUT_INTERFACE_h
#define _OUTPUT_INTERFACE_h

#include "arduino.h"

#define WHITELINE_CODE_PIN0       6U	// D6
#define WHITELINE_CODE_PIN1       7U	// D7
#define WHITELINE_CODE_PIN2       8U	// D8
#define OPPONENT_LOCATION_PIN0    A4
#define OPPONENT_LOCATION_PIN1    A5
#define INT_WHITELINE_PIN         5U	// D5
#define INT_OPPONENT_SPOTTED_PIN  4U	// D4
#define INT_OPPONENT_NEAR_PIN     3U	// D3

#define INT_WHITELINE         0
#define INT_OPPONENT_SPOTTED  1
#define INT_OPPONENT_NEAR     2

void init_whiteline_code();
void init_opponent_location();
void init_outgoing_interrupts();

void write_whiteline_code(int* whiteline_code);       // 3 elements    
void write_opponent_location(int* opponent_loc);      // 2 elements
void write_outgoing_interrupts(int* outgoing_ints);   // 3 elements

#endif

