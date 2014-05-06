import serial
import sys

# Octave grafica
# load lecturasGyro 
# plot(1:length(lecturasGyro),lecturasGyro)
# print("3sinMoverseY_adelante.jpg")

## Abrir el puerto de arduino
abierto = False
while(abierto == False):
  try:
    ser = serial.Serial('/dev/ttyUSB1', 9600)
    abierto = True
    break
  except serial.SerialException:
    abierto = False 

f = open(raw_input('Nombre de archivo: '),'w')

while True:
  line = ser.readline()
  print line
  f.write(line)


