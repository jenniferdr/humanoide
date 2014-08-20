  #include <HServo.h>
  #include <ax12.h>
  #include <BioloidController.h>
  #include "poses.h"
  
  BioloidController bioloid = BioloidController(1000000);
  HServo myservoB;
  HServo myservoA;

  int pos = 0; 
  // Rango de vision hasta segundo nivel = 1,28 m
  
  void setup() 
  { 
    myservoB.attach(12);  // puerto 12 (B) o 13 (A) abajo 
    myservoA.attach(13);  // arriba
    
    bioloid.loadPose(pose_1);
    bioloid.readPose();
    bioloid.interpolateSetup(300);
    while(bioloid.interpolating > 0){
      bioloid.interpolateStep();
      delay(3);
    }
  } 
 
  void loop() 
  { 
    //ar_m();
    //ar_d();
    //ar_i();
    //ab_m();
    //ab_d();
    //ab_i();
    //aar_m();
    //aar_d();
    aar_i();
    
    delay(4000);
    
  }
  
void ar_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(70);
}

void ar_d(){
  myservoB.write(7);
  delay(100);
  myservoA.write(80);
}

void ar_i(){
  myservoB.write(118);
  delay(100);
  myservoA.write(80);
}

void ab_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(34);
}

void ab_i(){
  myservoB.write(140);
  delay(100);
  myservoA.write(45);
}

void ab_d(){
  myservoB.write(10);
  delay(100);
  myservoA.write(50);
}

void aar_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(90);
}

void aar_d(){
  myservoB.write(8);
  delay(100);
  myservoA.write(90);
}

void aar_i(){
  myservoB.write(118);
  delay(100);
  myservoA.write(90);
}
