#include <ax12.h>
#include <BioloidController.h>
#include "poses3.h"

BioloidController bioloid = BioloidController(1000000);

// Giroscopio
int gyroX = 2;
int gyroY = 0;

int velocidadX;
int velocidadY;

void setup(){
  // stand up slowly
  delay(100);       // recommended pause
  Serial.begin(9600);

  pinMode(gyroX,INPUT);
  pinMode(gyroY,INPUT);  

  bioloid.loadPose(pose_2);
  bioloid.readPose();
  bioloid.interpolateSetup(300);
  while(bioloid.interpolating > 0){
    bioloid.interpolateStep();
    delay(3);
  }

  // start our walking
  bioloid.playSeq(camina);
}

void loop(){
  bioloid.playSeq(camina);
  while(bioloid.playing){
    bioloid.play();
    balance();
  } 
}

void balance(){

    // Lectura promediada
    
}

