// 
// 
// 

#include "sensorino_interface.h"

void init_opponent_location() 
{	
	pinMode(OPPONENT_LOCATION_PIN0, INPUT);
	pinMode(OPPONENT_LOCATION_PIN1, INPUT);
}

void init_opponent_spotted() 
{
	pinMode(INT_OPPONENT_SPOTTED_PIN, INPUT);
}

void init_start_signal() 
{
	pinMode(START_PIN, INPUT);
	digitalWrite(START_PIN, HIGH); //turn on pull-up resistors	
}

int read_opponent_location() 
{
	int opponent_loc0 = digitalRead(OPPONENT_LOCATION_PIN0);
	int opponent_loc1 = digitalRead(OPPONENT_LOCATION_PIN1);
	if (opponent_loc0 == 0 && opponent_loc1 == 0)
		return OPLOC_CENTER_MID;
	if (opponent_loc0 == 0 && opponent_loc1 == 1)
		return OPLOC_CENTER;
	if (opponent_loc0 == 1 && opponent_loc1 == 0)
		return OPLOC_FAR_LEFT;
	if (opponent_loc0 == 1 && opponent_loc1 == 1)
		return OPLOC_FAR_RIGHT;
}

int read_opponent_spotted() 
{
	return digitalRead(INT_OPPONENT_SPOTTED_PIN);
}

int	read_start_signal() 
{
	return digitalRead(START_PIN);
}




