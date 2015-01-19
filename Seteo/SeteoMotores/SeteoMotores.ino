/* Control y manipulacion de valores como torque , tmp y voltaje
 * torque de [512 - 1023]  actual = 800
 * tmp de [-5 - 85] actual = 30  
 */

#include <ax12.h>

int temp;
int torque;
int q = 1;

void setup(){
  
temp = 30;
torque = 800;
    Serial.begin(9600);
   
/* Proceso de marcar el valor indicado de tmp y torque 
 * De todos los motores juntos
 * Cambiar variable temp y torque para cambiar los valores
 */
    while(q < 18){
      SetTorqueL(q, torque); 
      SetTemperature(q,temp);
      SetAlarm(q);
      q = q+1;
    }
   
}

void loop(){
    
    int i = 1;
    
    while(i < 18){  
      Serial.print(" MOTOR CON ID ");
      Serial.print(i);
      // imprimir rango inferior del torque
      Serial.print(" Torque Inferior \n ");
      int Tor = GetTorqueH(i);
      Serial.print(Tor);
      // imprimir rango superior del torque
      Tor = GetTorqueL(i);
      Serial.print("Torque Superior \n");
      Serial.print(Tor);
      // imprimir temperatura
      int Tmp = GetTemperature(i);
      Serial.print("Temperatura \n ");
      Serial.print(Tmp);
       i = i +1;     
      delay(500);
  }
}

