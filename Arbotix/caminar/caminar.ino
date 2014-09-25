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
#include "posesVoltearIzquierda.h"
#include "pararseBocaArriba.h"

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
  
   if (ent == "w"){  
      bioloid.playSeq(camina);
   } else if (ent == "a") {
      bioloid.playSeq(voltearIzq);
   } else if (ent == "d"){
      bioloid.playSeq(voltearDer);
   } else if (ent == "r"){
     ab_m();
   } else if (ent == "u"){
     ab_d();
   } else if (ent == "y"){
     ar_m();
   }else if (ent == "t"){
     aar_m();
   }else if (ent == "o"){
     ar_d();
   }else if (ent == "i"){
     aar_d();
   }else if (ent == "g"){
     ar_i();
   }else if (ent == "f"){
     aar_i();
   }else if (ent == "p"){
     ab_i();
   }
}

ros::ServiceServer<Test::Request, Test::Response> server("moverRobot", &callback);

std_msgs::String str_msg;

void setup(){
  
  //Serial.begin(9600);
  myservoB.attach(12);  // puerto 12 (B) o 13 (A) abajo 
  myservoA.attach(13);  // arriba
  ar_m();
    
  pinMode(puertoGyroX,INPUT);
  pinMode(puertoGyroY,INPUT);  
  
  nh.initNode();
  nh.advertiseService(server);

  // pararse lentamente
  delay(100);
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
  
  t.update();
  
  if(de_pie){
    while(bioloid.playing) {
     t.update();
     nh.spinOnce();
     bioloid.play();
   }
   nh.spinOnce();
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
  
  //Serial.println(" Eje X \n ");
  //Serial.println(velocidadX);
  //Serial.println(" Eje Y \n ");
  //Serial.println(velocidadY);
  
  int errorX = velocidadX - inicialGyroX;
  int errorY = velocidadY - inicialGyroY;
  
  /*Serial.println(" Error X \n ");
  Serial.println(errorX);
  Serial.println(" Error Y \n ");
  Serial.println(errorY);*/
  
  int errorEscaladoX = (errorX*4)/18; // Motores 15 y 16
  int errorEscaladoX2 = (errorX*4)/54;
  int errorEscaladoY = (errorY*4)/20;
  
  // Modificar posicion de los motores 15 y 16
  SetPosition(15 , GetPosition(15) + errorEscaladoX);
  SetPosition(16 , GetPosition(16) - errorEscaladoX);
  
  // Modificar pos de motores 13 y 14 rodillas
  //SetPosition(13 , GetPosition(13) + errorEscaladoX2);
  //SetPosition(14 , GetPosition(14) - errorEscaladoX2);
  
  // Modificar pos de los motores 17 y 18  (Info del eje Y)
  //SetPosition(17 , GetPosition(17) - errorEscaladoY);
  //SetPosition(18 , GetPosition(18) - errorEscaladoY);
  
  if(errorX >= 100){
    de_pie = false;
    boca_arriba = true;
  }else if (errorX<= -60){
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
  
  //Serial.println(" Eje X inicial \n ");
  //Serial.println(inicialGyroX);
  //Serial.println(" Eje Y inicial\n ");
  //Serial.println(inicialGyroY);
}

// ********** Para mover los motores de la camara ********
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
