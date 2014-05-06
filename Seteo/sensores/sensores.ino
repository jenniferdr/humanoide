/* Controlar y modificar el sensor de Gyro en sus ejes X y Y
*/
// Inicializacion de los pines a utilizar
int sensorpinX = 2;//1
int sensorY = 0;//0
int X;
int Y;

void setup(){
  // Inicializacion de los sensores
    
    Serial.begin(9600); // Baudios
    pinMode(sensorpinX,INPUT);
    pinMode(sensorY,INPUT);
    digitalWrite(13,HIGH);
    delay(10);
    X = analogRead(sensorpinX);
    Y = analogRead(sensorY);
    digitalWrite(13,LOW);
}

void loop(){
  int i = 0;
  
  // Promedio de la lectura de los ejes
  X = analogRead(sensorpinX);
  Y = analogRead(sensorY);
  while (i < 9){
    X = analogRead(sensorpinX) + X;
    Y = analogRead(sensorY) + Y;
    
    delay(100);
    i = i+1;
  }
  int Gyro = 1;
  X = X/10;
  Y = Y/10;
  Serial.print(" Eje X \n ");
  Serial.print(X);
  Serial.print(" Eje Y \n ");
  Serial.print(Y);
  int o = random(0,1023);

}
