#ifndef _WHITELINESENSORTEST_h
#define _WHITELINESENSORTEST_h

#if defined(ARDUINO) && ARDUINO >= 100
  #include "arduino.h"
#else
  #include "WProgram.h"
#endif

#include "../Sensorino/sensor_interface.h"
#include "../Sensorino/output_interface.h"

class InterruptsTestClass: public FuriosityTest
{
 public:
  virtual void init();
  virtual void loop();  
  int whiteline_code_testcase[64] = {0, 0, 0, 0, 
                              0, 0, 0, 1, 
                              0, 0, 1, 0, 
                              0, 0, 1, 1,
                              0, 1, 0, 0,
                              0, 1, 0, 1,
                              0, 1, 1, 0,
                              0, 1, 1, 1,
                              1, 0, 0, 0,
                              1, 0, 0, 1,
                              1, 0, 1, 0,
                              1, 0, 1, 1,
                              1, 1, 0, 0,
                              1, 1, 0, 1,
                              1, 1, 1, 0,
                              1, 1, 1, 1}; 
  int keyence_code_testcase[24] = {0, 0, 0,
                            0, 0, 1,
                            0, 1, 0,
                            0, 1, 1,
                            1, 0, 0,
                            1, 0, 1,
                            1, 1, 0,
                            1, 1, 1};
  int keyence_reading[3];     
  int whiteline_reading[4];   
  int omron_reading;
  
  int whiteline_code[3];          
  int opponent_location_code[2];  
  int outgoing_interrupts[3];    
  
  int countKeyence = 0;
  int countWhiteline = 0;
  int count1 = 0;
  int count2 = 0;
};

extern InterruptsTestClass InterruptsTest;

#endif

