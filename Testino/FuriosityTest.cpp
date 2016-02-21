#include "FuriosityTest.h"

void FuriosityTest::init_output_pins(int* pins, int pin_count)
{
	for (int i = 0; i < pin_count; i++)
	{
		pinMode(pins[i], OUTPUT);
	}
}
void FuriosityTest::init_input_pins(int* pins, int pin_count)
{
	for (int i = 0; i < pin_count; i++)
	{
		pinMode(pins[i], INPUT);
	}
}

