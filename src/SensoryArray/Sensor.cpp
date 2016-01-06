#include "Sensor.h"

//Sensor Constructor

Sensor::Sensor(String name, int _pin, int _boardId, int _testPin)
	{
		sensorName = name;
		Pin = _pin;  //signal out pin of sensor
    testPin = _testPin;
		samplingRate = 5000; //1 second in millis
		timeLastSampled=0;
    boardId = _boardId;
		
    if (_testPin = 0)
      {testAvailable = false;}
      else
        {testAvailable = true;}

      testCycles = 0;
    pinMode(_pin, INPUT);
	}
	
	
int Sensor::takeMeasurement(void)
	{
    //check if sensor is in test mode
    if (testCycles >0)
    {
      digitalWrite(testPin, HIGH);
    }

    //take measurement
    int measurement = analogRead(Pin);

    if (testCycles>0)
    {
      digitalWrite(testPin, LOW);
      testCycles = testCycles--;
    }
    //Send measurement details over serial
    String measurementStatement ="{\n";
    measurementStatement +=
            " \"boardId\" : " + String(boardId) + ",\n"
          + " \"sensorName\" : \"" + String(sensorName) + "\" ,\n"
          + " \"sensorId\" : \"" + String(sensorId) + "\" ,\n"
          + " \"measurement\" : " + String(measurement) + " ,\n"
          + " \"sampleTime\" : " + String(millis()) + ",\n"
          + " \"samplingRate\" : " + String(samplingRate) + "\n"
          + " \"testCycles\" : " + String(testCycles) + "\n"
          + " }"
      ;
      Serial.println(measurementStatement);
    timeLastSampled = millis();
    return measurement;
	}

void Sensor::changeSamplingRate(int newrate)
  {
    samplingRate = newrate;
  }

void Sensor::test(int testCycles)
  {
    testCycles = testCycles;
  }

//Send details of sensor object to remote (over serial)
void Sensor::getDetails(void)
{
   String sensorDetails ="{\n";
  sensorDetails +=
        " \"boardId\" : " + String(boardId) + ",\n"
      + " \"sensorName\" : \"" + String(sensorName) + "\" ,\n"
      + " \"sensorId\" : \"" + String(sensorId) + "\" ,\n"
      + " \"pin\" : " + String(Pin) + " ,\n"
      + " \"sensorType\" : " + String(sensorType) + ",\n"
      + " \"samplingRate\" : " + String(samplingRate) + "\n"
      + " \"timeLastSampled\" : " + String(timeLastSampled) + "\n"
      + " \"testAvailable\" : " + String(testAvailable) + "\n"
      + " \"testPin\" : " + String(testPin) + "\n"
      + " \"testCycles\" : " + String(testCycles) + "\n"
      + " }"
  ;
  Serial.println(sensorDetails);
}
