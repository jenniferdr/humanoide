#include <ax12.h>
#include <BioloidController.h>
//#include "poses.h"

int Temp;
int sensorpinX = 1;
int sensorY = 0;
int X;
int Y;
int q = 1;
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
    
    while(q < 18){
      SetTorqueL(q, 800); 
      SetAlarm(q);
      q = q+1;
    }
    //SetTemperature(4, 30);
}

void loop(){
 /* X = analogRead(sensorpinX);
  Y = analogRead(sensorY);
    Serial.print(" tempe \n ");
    Temp = GetTorqueH(1);
    Serial.print(Temp);
    Temp = GetTorqueL(1);
    Serial.print("TOr");
    Serial.print(Temp);
    
    delay(500);
  }*/
}
