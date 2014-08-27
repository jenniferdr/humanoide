//Secciones de la camara 
1 Arriba-Medio
2 Derecha-Arriba
3 Izquierda-Arriba
4 Izquierda-Inferior
5 Izquierda-Inferior-Patada
6 Derecha-Inferior-Patada
7 Derecha-Inferior

CamAbajoMedio:

  bool esVisiblePelota;
  par posicionPelota;
  int cuadrantePelota;
  Mat imgOriginal

CamAbajoMedio(Mat imagen){
  this.imgOriginal = imagen;
}

bool estaEnDerechaArriba(){
  
  if (posicionPelota.x > 1/3de pantalla && posicionPelota.x < 2/3depantalla && posicionPelota.y < 1/6 de pantalla ){

	return true
}

void cuadrantePelota(){
  this.posicionPelota = deteccionPelota.obtenerPosicion()
  if estaEnDerechaArriba:
     cuadrantePelota = 1 
   ....

}

void accion (){

  if (deteccionPelota.esVisible(imgOriginal)){
    cuadrantePelota()
    case (this.cuadrantePelota) 
	1: adelante
	2: derecha
	3: izquierda
	4: izquierda
	5: PatadaIzq
	6: PatadaDer
	7: derecha

  } else {
     movercamara()
  }

}

