#include "Sensor.h"
#include "Board.h"
//device constants
  //So that remote can idenify this board from others
Board myboard = Board(1,"prototypeUno");



//instantiate array of sensors (one record per sensor on board)
  Sensor sensorList[]={Sensor("distanceSensor",A0,myboard.boardId,0)};
  myboard.sensorList[]={Sensor("distanceSensor",A0,myboard.boardId,0)}; //myboard does not name a type?
  

const int SensorCount = (sizeof(sensorList)/sizeof(sensorList[0]));

int main(){
      Serial.begin(9600);
      Serial.print("Initializing SensorArray");

      //Make sensorId attribute same as index 
      int i=0;
      for (i=0 ; i < SensorCount ; i++)
        {sensorList[i].sensorId = i;}
  
  while (1){
    //loop throught all sensors, if time to take new measurement, take measurement
    int i =0;
    for (i=0 ; i < SensorCount ; i++)
    {
      if ((sensorList[i].timeLastSampled + sensorList[i].samplingRate)<millis())
        {
            sensorList[i].takeMeasurement();
        }
        else
        {
          //Do nothing 
        }  
    }

    //check for possible input command on serial receive buffer
    while (Serial.available()>0)
    {
        String cmd ="";
        cmd = Serial.readStringUntil('\n');
        //cleanse string
          cmd.trim();
          cmd.toLowerCase();
          
            char nullptr =0;
            char newline = 10;
            char tab = 11;
            char carriagereturn = 13;
            cmd.replace(newline,nullptr);
            cmd.replace(tab,nullptr);
            cmd.replace(carriagereturn,nullptr);
        execCmd(cmd);
    }

  }  
  
}

  
void execCmd(String myCmd)
  {
    /*
      Expected string format is: SensorList[sensorID].cmdName(param1)
      example: SensorList[0].test(5)
      Note: if a new command is possible, it should be mapped here
    */
    int sensoridStart=myCmd.indexOf("[")+1;
    int sensoridEnd=myCmd.indexOf("]");
    int sensorId =(sensoridStart==sensoridEnd+1? "":myCmd.substring(sensoridStart,sensoridEnd) ).toInt();
   
    int cmdStart = myCmd.indexOf(".")+1;
    int cmdEnd = myCmd.indexOf("(");
    String cmd =(cmdStart==cmdEnd+1? "":myCmd.substring(cmdStart,cmdEnd) );
    
    int param1Start = myCmd.indexOf("(")+1;
    int param1End = myCmd.indexOf(")");
    int param1 =(param1Start==param1End+1? "":myCmd.substring(param1Start,param1End) ).toInt();
  
    if (cmd=="takemeasurement")
      {
        sensorList[sensorId].takeMeasurement();
        Serial.println("Cmd recognized: takeMeasurement");
      }
    else if (cmd=="changesamplingrate")
      {
        sensorList[sensorId].changeSamplingRate(param1);
        Serial.println("Cmd recognized: changeSamplingRate");
      }
    else if (cmd=="test")
      {
        sensorList[sensorId].test(param1);
        Serial.println("Cmd recognized: test");
      }
    else if (cmd=="getdetails")
      {
        sensorList[sensorId].getDetails();
        Serial.println("Cmd recognized: getDetails");
      }
    else 
      {
        Serial.println("Cmd not recognized");
      }
    
  }
