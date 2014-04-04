#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

int sensorpinX = 2;//1
int sensorY = 0;//0
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
    
    
    /*bioloid.loadPose(pose_2);
    bioloid.readPose();
    bioloid.interpolateSetup(500);
    while(bioloid.interpolating > 0){
       bioloid.interpolateStep();
       delay(3);
    }
   
    // start our walking
    bioloid.playSeq(camina);*/
}

void loop(){
  int i = 0;
  
  X = analogRead(sensorpinX);
  Y = analogRead(sensorY);
  while (i < 9){
    X = analogRead(sensorpinX) + X;
    Y = analogRead(sensorY) + Y;
    
    delay(100);
    i = i+1;
  }
  int Gyro = 1;
  X = X/10;
  Y = Y/10;
  Serial.print(" Eje X \n ");
  Serial.print(X);
  Serial.print(" Eje Y \n ");
  Serial.print(Y);
  int o = random(0,1023);
 
  if (X<240){
    SetPosition(10,o);
    Gyro = 0;  
  } else if (X>300){
    SetPosition(10,o);
    Gyro = 0;
  } //else {
    //bioloid.play();

 /* if (Gyro == 0){
    SetPosition(10,o);
  
  }*/    
    
    //delay(500);
  //}
}
