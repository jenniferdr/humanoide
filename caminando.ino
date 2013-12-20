#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

BioloidController bioloid = BioloidController(1000000);

void setup(){
    // stand up slowly
    delay(100);                    // recommended pause
    bioloid.loadPose(pose_1);
    bioloid.readPose();
    bioloid.interpolateSetup(500);
    while(bioloid.interpolating > 0){
        bioloid.interpolateStep();
        delay(3);
    }
    
    // start our walking
    bioloid.playSeq(camina);
}

void loop(){
    bioloid.play();
}
