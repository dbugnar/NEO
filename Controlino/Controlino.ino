#include "control_interface.h"
#include "sensorino_interface.h"
#define START 0
#define SEARCH 1
#define CENTER 2
#define DESTROY 3
#define DIR_CONTROL 4

int current_state = START;
int next_state = SEARCH;

int motor_left = 0;
int motor_right = 0;

void setup() {	
	init_opponent_location();
	init_opponent_spotted();
	init_start_signal();
}

void loop() {
	switch (current_state){
	case START:
		// Wait for remote control signal
		int start_signal = read_start_signal();

		motor_left = DONT_MOVE;
		motor_right = DONT_MOVE;
		if (start_signal == HIGH)
		{
			next_state = SEARCH;
		} 
		else
		{
			next_state = START;
		}
		break;

	case SEARCH:
		// Rotate right until INT_OPPONENT_SPOTTED interrupt is triggered
		int opponent_spotted = read_opponent_spotted();
		if (opponent_spotted == HIGH)
		{			
			motor_left = DONT_MOVE;
			motor_right = DONT_MOVE;
			next_state = CENTER;
		}
		else
		{
			motor_left = MAX_SPEED;
			motor_right = -1 * MAX_SPEED;
			next_state = SEARCH;
		}
		break;

	case CENTER:
		int opponent_location = read_opponent_location();
		if (opponent_location == OPLOC_FAR_LEFT)
		{
			motor_left = -1 * CENTER_CONTROL_OFFSET;
			motor_right = CENTER_CONTROL_OFFSET;
			next_state = CENTER;
		}
		else if (opponent_location == OPLOC_FAR_RIGHT)
		{
			motor_left = CENTER_CONTROL_OFFSET;
			motor_right = -1 * CENTER_CONTROL_OFFSET;
			next_state = CENTER;
		}
		else
		{
			motor_left = MAX_SPEED;
			motor_right = MAX_SPEED;
			next_state = DESTROY;
		}
		break;

	case DESTROY:
		// Full speed ahead

		motor_left = MAX_SPEED;
		motor_right = MAX_SPEED;
		next_state = DIR_CONTROL;
		break;

	case DIR_CONTROL:
		// Given the current sensor status (and maybe last values) infer 
		// direction error control in order to face the opponent.
		int opponent_location = read_opponent_location();
		if (opponent_location == OPLOC_FAR_LEFT)
		{
			motor_left += -1 * DIR_CONTROL_OFFSET;
			motor_right += DONT_MOVE;
			next_state = DESTROY;
		}
		else if (opponent_location == OPLOC_FAR_RIGHT)
		{
			motor_left += DONT_MOVE;
			motor_right += -1 * DIR_CONTROL_OFFSET;
			next_state = DESTROY;
		}
		else
		{
			motor_left += DONT_MOVE;
			motor_right += DONT_MOVE;
			next_state = DESTROY;
		}
		break;
	}

	//writeMotors(motor_left, motor_right);
	current_state = next_state;
}