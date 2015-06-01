//#include "Arduino.h"
#include "Sensor.h"

//Sensor Constructor

Sensor::Sensor(String name, int _pin, int _boardId)
	{
		sensorName = name;
		Pin = _pin;  //signal out pin of sensor
		samplingRate = 5000; //1 second in millis
		timeLastSampled=0;
        boardId = _boardId;
		pinMode(_pin, INPUT);
	}
	
	
int Sensor::takeMeasurement(void)
	{
   
    //take measurement
    int measurement = analogRead(Pin);

    //Send measurement details over serial
    String measurementStatement ="{\n";
    measurementStatement +=
            " \"boardId\" : " + String(boardId) + ",\n"
          + " \"sensorName\" : \"" + String(sensorName) + "\" ,\n"
          + " \"sensorId\" : \"" + String(sensorId) + "\" ,\n"
          + " \"measurement\" : " + String(measurement) + " ,\n"
          + " \"sampleTime\" : " + String(millis()) + ",\n"
          + " \"samplingRate\" : " + String(samplingRate) + "\n"
          + " }"
      ;
      Serial.println(measurementStatement);
    timeLastSampled = millis();
    return measurement;
	}
