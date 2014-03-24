#include <ax12.h>
#include <BioloidController.h>
//#include "poses.h"

int Temp;
int sensorpinX = 1;
int sensorY = 0;
int X;
int Y;
BioloidController bioloid = BioloidController(1000000);

void setup(){
    // stand up slowly
    delay(100);       // recommended pause
    Serial.begin(9600);
    pinMode(sensorpinX,INPUT);
    pinMode(sensorY,INPUT);
    digitalWrite(13,HIGH);
    delay(10);
    X = analogRead(sensorpinX);
    Y = analogRead(sensorY);
  
    digitalWrite(13,LOW);
    SetTemperature(4, 30);
    SetAlarm(4);
    //bioloid.loadPose(pose_1);
    //bioloid.readPose();
    //bioloid.interpolateSetup(500);
   // while(bioloid.interpolating > 0){
        //bioloid.interpolateStep();
        //delay(3);
   // }
   
    // start our walking
   // bioloid.playSeq(camina);
}

void loop(){
 /* X = analogRead(sensorpinX);
  Y = analogRead(sensorY);
  if (X<248){
    SetPosition(5,100);
  } else if (X>253){
    SetPosition(5,512);
  } else if(Y>253){
    SetPosition(6,100);
  } else if (Y<248){
    SetPosition(6,512);
  } else {*/ 
    //bioloid.play();    
    Serial.print(" tempe \n ");
    Temp = GetTemperature(11);
    Serial.print(Temp);
    delay(500);
  //}
}
