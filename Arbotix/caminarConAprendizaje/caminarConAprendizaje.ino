/* Para caminar directamente con la tarjeta Arbotix
 * Se debe tener en la misma carpeta las poses necesarias
 * 
 */
#include <HServo.h>

#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"
#include "pararseBocaAbajo.h"
#include "posesVoltearDerecha.h"
#include "girarIzquierda.h"
#include "pararseBocaArriba.h"
#include "patadaDerecha.h"
#include "patadaIzquierda.h"
#include "caminarPoco.h"
#include "aplausos.h"
#include "unBrazo.h"

#include <Event.h>
#include <Timer.h>
#include <Servo.h>

// Librerias para ROS
#include <ros.h>
#include <std_msgs/String.h>
#include <rosserial_arduino/Test.h>

BioloidController bioloid = BioloidController(1000000);

// Puertos Giroscopio
int puertoGyroX = 5;
int puertoGyroY = 7;

// Lectura inicial, sera el 'centro'
int inicialGyroX = 0;
int inicialGyroY = 0;

// Valores de velocidad angular, cambiante.
int velocidadX;
int velocidadY;
// Motores de la Camara
HServo myservoB;
HServo myservoA;

Timer t;
boolean de_pie = true;
boolean boca_arriba= false;

// inicializando el nodo que maneja el servicio
ros::NodeHandle  nh;
using rosserial_arduino::Test;

// opcion para puerto serial
int opcion;


// Funcion CallBack para definir el servicio a prestar
void callback(const Test::Request & req, Test::Response & res){
  String ent = String(req.input);
  res.output = req.input;
  
   if (ent == "0"){  
     bioloid.playSeq(caminaPoco); // caminar pequeño
   } else if (ent == "1") {
     bioloid.playSeq(camina);
   } else if (ent == "2") {
     bioloid.playSeq(camina); 
     while(bioloid.playing) {
       t.update();
       bioloid.play();
     }
     bioloid.playSeq(camina);
   } else if (ent == "3"){
      bioloid.playSeq(voltearDer);
   } else if (ent == "4") {
      bioloid.playSeq(voltearIzq);
   } else if (ent == "5"){
      bioloid.playSeq(voltearDer);
      while(bioloid.playing) {
       t.update();
       bioloid.play();
     }
     bioloid.playSeq(voltearDer);
   } else if (ent == "6") {
      bioloid.playSeq(voltearIzq);
      while(bioloid.playing) {
       t.update();
       bioloid.play();
     }
     bioloid.playSeq(voltearIzq);
   } else if (ent == "q"){
     bioloid.playSeq(patadaDerecha);
   } else if (ent == "e"){
     bioloid.playSeq(patadaIzquierda);
   } else if (ent == "r"){
     ab_m();
   } else if (ent == "u"){
     ab_d();
   } else if (ent == "y"){
     ar_m();
   }else if (ent == "o"){
     ar_d();
   }else if (ent == "g"){
     ar_i();
   }else if (ent == "p"){
     ab_i();
   }else if (ent == "t"){
     aar_m();
   }else if (ent == "i"){
     aar_d();
   }else if (ent == "f"){
     aar_i();
   }
   else if (ent == "n"){
      bioloid.playSeq(brazo);
   }else if (ent == "m"){
     bioloid.playSeq(ambos);
   }
   
   while(bioloid.playing) {
     t.update();
     //nh.spinOnce();
     bioloid.play();
   }
}

ros::ServiceServer<Test::Request, Test::Response> server("moverRobot", &callback);

std_msgs::String str_msg;

void setup(){
  Serial.begin(9600);
  myservoB.attach(12);  // puerto 12 (B) o 13 (A) abajo 
  myservoA.attach(13);  // arriba
  ab_m();
    
  pinMode(puertoGyroX,INPUT);
  pinMode(puertoGyroY,INPUT);  
  
  nh.initNode();
  nh.advertiseService(server);

  // pararse lentamente
  delay(70);
  bioloid.loadPose(pose_1);
  bioloid.readPose();
  bioloid.interpolateSetup(300);
  while(bioloid.interpolating > 0){
    bioloid.interpolateStep();
    delay(3);
  }
  t.every(300,balance);
  
  inicializarGyro();

}

void loop(){
  
  if(de_pie){
    nh.spinOnce();
    t.update();
  }else{
    if (!boca_arriba){
      bioloid.playSeq(levantarse_boca_abajo);
    }else{
      bioloid.playSeq(levantarse_boca_arriba);
    }
    bioloid.play();
    while(bioloid.playing){
      bioloid.play();
    }
    de_pie= true;
  }
}

void balance(){
  
  int X = 0;
  int Y = 0;
  int i = 0;

  // Lectura promediada
  while(i<10){
    i = i + 1;
    X = analogRead(puertoGyroX) + X;
    Y = analogRead(puertoGyroY) + Y;  
    delay(1);
  }
  velocidadX = X/10;
  velocidadY = Y/10;
  
  int errorX = velocidadX - inicialGyroX;
  int errorY = velocidadY - inicialGyroY;
  
  int errorEscaladoX = (errorX*4)/18; // Motores 15 y 16
  int errorEscaladoX2 = (errorX*4)/54;
  int errorEscaladoY = (errorY*4)/20;
  
  if(errorX >= 100){
    de_pie = false;
    boca_arriba = true;
  }else if (errorX<= -80){
    de_pie = false;
    boca_arriba = false;
  }
}

void inicializarGyro()
{
  delay(15000);
  int i = 0;

  // Lectura promediada
  while(i<10){
    i = i + 1;
    inicialGyroX = analogRead(puertoGyroX) + inicialGyroX;
    inicialGyroY = analogRead(puertoGyroY) + inicialGyroY;  
    delay(100);
  }
  inicialGyroX = inicialGyroX/10;
  inicialGyroY = inicialGyroY/10;
}

// ********** Para mover los motores de la camara ********
  
void ar_m(){
  myservoB.write(31);
  delay(100);
  myservoA.write(65);
}

void ar_d(){
  myservoB.write(5);
  delay(100);
  myservoA.write(90);
}

void ar_i(){
  myservoB.write(83);
  delay(100);
  myservoA.write(73);
}

void ab_m(){
  myservoB.write(30);
  delay(100);
  myservoA.write(35);
}

void ab_i(){
  myservoB.write(90);
  delay(100);
  myservoA.write(40);
}

void ab_d(){
  myservoB.write(15);
  delay(100);
  myservoA.write(60);
}

void aar_m(){
  myservoB.write(31);
  delay(100);
  myservoA.write(90);
}

void aar_d(){
  myservoB.write(10);
  delay(100);
  myservoA.write(90);
}

void aar_i(){
  myservoB.write(85);
  delay(100);
  myservoA.write(90);
}
