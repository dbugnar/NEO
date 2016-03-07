// 
// 
// 

#include "control_interface.h"

void writeMotors(int a, int b)
{
	rawPacket sRawPacket_mds = { '#', '#', '#', 0, 0, 0 };
	sRawPacket_mds.sMotorCommand.pMotorR_sds16 = (int16_t)(m1 * 0.925);
	sRawPacket_mds.sMotorCommand.pMotorL_sds16 = -m2;
	Serial1.write(sRawPacket_mds.data, BUFFER_LENGTH);
}

