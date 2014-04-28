#include <ax12.h>
#include <BioloidController.h>
#include "poses.h"

BioloidController bioloid = BioloidController(1000000);

// Puertos Giroscopio
int puertoGyroX = 2;
int puertoGyroY = 0;

// Lectura inicial, sera el 'centro'
int inicialGyroX = 0;
int inicialGyroY = 0;

// Valores de velocidad angular, cambiante.
int velocidadX;
int velocidadY;

void setup(){
  // stand up slowly
  delay(100);       // recommended pause
  Serial.begin(9600);

  pinMode(puertoGyroX,INPUT);
  pinMode(puertoGyroY,INPUT);  

  bioloid.loadPose(pose_1);
  bioloid.readPose();
  bioloid.interpolateSetup(300);
  while(bioloid.interpolating > 0){
    bioloid.interpolateStep();
    delay(3);
  }
  
  inicializarGyro();
  // start our walking
  bioloid.playSeq(camina);
}

void loop(){
  //bioloid.playSeq(camina);
  //while(bioloid.playing){
    //bioloid.play();
    balance();
  //} 
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
  Serial.println(velocidadX);
  //Serial.println(" Eje Y \n ");
  //Serial.println(velocidadY);
  
  int errorX = velocidadX - inicialGyroX;
  int errorY = velocidadY - inicialGyroY;
  
  /*Serial.println(" Error X \n ");
  Serial.println(errorX);
  Serial.println(" Error Y \n ");
  Serial.println(errorY);*/
  
  int errorEscaladoX = (errorX*4)/54;
  int errorEscaladoY = (errorY*4)/18;
  
}

void inicializarGyro()
{
  delay(10000);
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
  
  Serial.println(" Eje X inicial \n ");
  Serial.println(inicialGyroX);
  Serial.println(" Eje Y inicial\n ");
  Serial.println(inicialGyroY);
}
