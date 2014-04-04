#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

BioloidController bioloid = BioloidController(1000000);

void setup(){
  // stand up slowly
  delay(100);       // recommended pause
  //   Serial.begin(9600);    

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
  bioloid.playSeq(walk);
  while(bioloid.playing){
    bioloid.play();
  }  
  //while(true){
  //bioloid.play();
  //}
}

