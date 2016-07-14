#ifndef Board_h
#define Board_h

#include "arduino.h"
#include "sensor.h"

class Board{
public:
	int boardId;
	String boardName;
	int sensorCount;
	Board(int,String);
  Sensor sensorList[20]; 
  //int countSensors(void);
};


#endif
