#include <HServo.h>

#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"
#include "pararseBocaAbajo.h"
#include "posesVoltearDerecha.h"
#include "posesVoltearIzquierda.h"
#include "pararseBocaArriba.h"
#include "posesPatadaDerecha.h"
#include "posesPatadaIzquierda.h"
#include <Event.h>
#include <Timer.h>
#include <Servo.h>

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
Timer t;
// opcion para puerto serial
int opcion;
boolean de_pie= true;
boolean boca_arriba= false;

void setup(){
  Serial.begin(9600);
  pinMode(puertoGyroX,INPUT);
  pinMode(puertoGyroY,INPUT); 
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

  while(bioloid.playing){
    t.update();
    bioloid.play();
  }
  if (Serial.available()>0){
    opcion = Serial.read();
    if(de_pie){
      switch (opcion){
      case 'w':
        bioloid.playSeq(camina); 
        break;      
      case 'a':
        bioloid.playSeq(voltearIzq);      
        break;      
      case 'd':
        bioloid.playSeq(voltearDer);
        break;
      case 'q':
        bioloid.playSeq(patadaIzquierda);
        break;
      case 'e':
        bioloid.playSeq(patadaDerecha);
        break;

      }
    }
    else{
      if (!boca_arriba){
        bioloid.playSeq(levantarse_boca_abajo);
      }
      else{
        bioloid.playSeq(levantarse_boca_arriba);
      }
      bioloid.play();
      while(bioloid.playing){
        bioloid.play();
      }
      de_pie= true;
    }
  }

  t.update();
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
  // SetPosition(15 , GetPosition(15) + errorEscaladoX);
  //SetPosition(16 , GetPosition(16) - errorEscaladoX);

  // Modificar pos de motores 13 y 14 rodillas
  //SetPosition(13 , GetPosition(13) + errorEscaladoX2);
  //SetPosition(14 , GetPosition(14) - errorEscaladoX2);

  // Modificar pos de los motores 17 y 18  (Info del eje Y)
  //SetPosition(17 , GetPosition(17) - errorEscaladoY);
  //SetPosition(18 , GetPosition(18) - errorEscaladoY);

  if(errorX >= 145){
    de_pie = false;
    boca_arriba = true;
  }
  else if (errorX<= -105){
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


