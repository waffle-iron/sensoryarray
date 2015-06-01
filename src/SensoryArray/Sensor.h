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
	bool testAvailable;
	int testPin;
	int testCycles;
	
	//sensor name, pin, boardid
	Sensor(String, int, int, int);
	int takeMeasurement(void);
	void changeSamplingRate(int);
	void test(int);
	void getDetails(void);
};

#endif
