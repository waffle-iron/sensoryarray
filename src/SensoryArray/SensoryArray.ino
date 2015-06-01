#include "Sensor.h"
//device constants
  //So that remote can idenify this board from others
  const int boardId = 1;

//instantiate array of sensors (one record per sensor on board)
  Sensor sensorList[]={
                        Sensor("distanceSensor",A0,boardId)
                      };

const int SensorCount = (sizeof(sensorList)/sizeof(sensorList[0]));


void setup()
  {
      Serial.begin(9600);
      Serial.print("Initializing SensorArray");

      //Make sensorId attribute same as index 
      int i=0;
      for (i=0 ; i < SensorCount ; i++)
        {sensorList[i].sensorId = i;} 
  }

  
void loop()
  {
    //loop throught all sensors, if time to take new measurement, take measurement
    int i =0;
    for (i=0 ; i < SensorCount ; i++)
    {
      if ((sensorList[i].timeLastSampled + sensorList[i].samplingRate)<millis())
        {
            sensorList[i].takeMeasurement();
        }
        else
        {}  
    }
  }
 
