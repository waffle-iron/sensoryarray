#ifndef Sensor_h
#define Sensor_h

#include "arduino.h"


//When adding a new attribute, please add to getDetails() method

class Sensor{
public:
    
    int boardId;
	String sensorName;
	int sensorId;
	int Pin;
	int sensorType;
	unsigned long samplingRate;
	unsigned long timeLastSampled;
	
	//sensor name, pin, boardid
	Sensor(String, int, int);
	int takeMeasurement(void);
	void changeSamplingRate(int);
};

#endif
