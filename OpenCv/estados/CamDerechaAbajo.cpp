

Class CamDerechaAbajo{

  Mat imgOriginal;

CamAbajoMedio(){
  this.imgOriginal = Tomarimagen;
}

void ubicarPelota (){

  if (deteccionPelota.esVisible(imgOriginal)){
    moverse(derecha);
    return true;
  } else {
    cam = new CamDerechaArriba();
    return cam.ubicarPelota();
  }

}

}
