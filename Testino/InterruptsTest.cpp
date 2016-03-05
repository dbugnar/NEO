// 
// 
// 

#include "InterruptsTest.h"

void InterruptsTestClass::init()
{
  Serial.begin(9600);
  count1 = 0;
  count2 = 0;
}

void InterruptsTestClass::loop()
{
  /************************Get sensor data****************************/
  /*********************Compute control codes*************************/
  /* Whiteline code:
  *
  *  000: Front    100: Back
  *  001: FrontRight   101: BackLeft
  *  010: FrontLeft    110: BackRight
  *  011: Left     111: Right
  */
  delay(3000);
  if (count1 <= 60) {
    Serial.print("Whiteline reading:\n");
    for(int i = 0; i < 4; i++) {
      whiteline_reading[i] = whiteline_code_testcase[count1 + i];
      Serial.print(whiteline_reading[i]);
      Serial.print(" ");
    }
    Serial.print("\nWhiteline code:\n");
    
    // WL_CODE[0] is computed as: (rl AND NOT(rr)) OR (NOT(fl) AND fr)
    whiteline_code[0] = (whiteline_reading[WHITELINE_REAR_LEFT] & (1 - whiteline_reading[WHITELINE_REAR_RIGHT])) |
      ((1 - whiteline_reading[WHITELINE_FRONT_LEFT]) & whiteline_reading[WHITELINE_FRONT_RIGHT]);
  
    // WL_CODE[1] is computed as: (NOT(rl) AND rr) OR (fl AND NOT(fr))
    whiteline_code[1] = ((1 - whiteline_reading[WHITELINE_REAR_LEFT]) & whiteline_reading[WHITELINE_REAR_RIGHT]) |
      (whiteline_reading[WHITELINE_FRONT_LEFT] & (1 - whiteline_reading[WHITELINE_FRONT_RIGHT]));
  
    // WL_CODE[2] is computed as: (NOT(fr) AND NOT(rr)) OR (NOT(rl) AND rr)
    whiteline_code[2] = ((1 - whiteline_reading[WHITELINE_FRONT_RIGHT]) & (1 - whiteline_reading[WHITELINE_REAR_RIGHT])) |
      ((1 - whiteline_reading[WHITELINE_REAR_LEFT]) & whiteline_reading[WHITELINE_REAR_RIGHT]);

    for(int i = 0; i < 3; i++) {
      Serial.print(whiteline_code[i]);
      Serial.print(" ");
    }
    Serial.print("\n");
    count1 += 4;
   } 
   if (count2 <= 21) {
    Serial.print("Keyence reading:\n");
    for(int i = 0; i < 3; i++) {
       keyence_reading[i] = keyence_code_testcase[count2 + i];
       Serial.print(keyence_reading[i]);
       Serial.print(" ");
    }
    Serial.print("\nOpponent location code:\n");
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

    Serial.print(opponent_location_code[0]);
    Serial.print(" ");
    Serial.print(opponent_location_code[1]);
    count2 += 3; 
}

InterruptsTestClass InterruptsTest;

