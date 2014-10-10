  #include <HServo.h>
  #include <ax12.h>
  #include <BioloidController.h>
  #include "poses.h"
  #include "posesVoltearDerecha.h"
  #include "posesVoltearIzquierda.h"
  
  BioloidController bioloid = BioloidController(1000000);
  HServo myservoB;
  HServo myservoA;

  int pos = 0; 
  // Rango de vision hasta segundo nivel = 1,28 m
  // Rango tercer nivel = 2,39 m
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
    ar_m();
    //ar_d();
    //ar_i();
    //ab_m();
    //ab_d();
    //ab_i();
    //aar_m();
    //aar_d();
    //aar_i();
    
    delay(4000);
    
  }
  
void ar_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(65);
}

void ar_d(){
  myservoB.write(12);
  delay(100);
  myservoA.write(90);
}

void ar_i(){
  myservoB.write(118);
  delay(100);
  myservoA.write(80);
}

void ab_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(35);
}

void ab_i(){
  myservoB.write(135);
  delay(100);
  myservoA.write(60);
}

void ab_d(){
  myservoB.write(20);
  delay(100);
  myservoA.write(60);
}

void aar_m(){
  myservoB.write(60);
  delay(100);
  myservoA.write(90);
}

void aar_d(){
  myservoB.write(20);
  delay(100);
  myservoA.write(110);
}

void aar_i(){
  myservoB.write(118);
  delay(100);
  myservoA.write(90);
}
