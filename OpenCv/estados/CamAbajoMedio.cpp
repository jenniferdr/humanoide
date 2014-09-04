//Secciones de la camara 
/* 1 Arriba-Medio
 * 2 Derecha-Arriba
 * 3 Izquierda-Arriba
 * 4 Izquierda-Inferior
 * 5 Izquierda-Inferior-Patada
 * 6 Derecha-Inferior-Patada
 * 7 Derecha-Inferior
*/

class CamAbajoMedio{

  par posicionPelota;
  bool enZonaPateo;
  Mat imgOriginal;

  // Puntos para seccionar imagen
  // Linea vertical izquierda
  CvPoint verticalIni;
  CvPoint verticalFin;
 
  // Linea vertical derecha
  CvPoint verticalIni2;
  CvPoint verticalFin2;

  // linea horizontal
  CvPoint horizontalIni;
  CvPoint horizontalFin;

  // linea vertical area de pateo
  CvPoint verticalIni3;
  CvPoint verticalFin3;

  // linea vertical del medio del area de pateo
  CvPoint verticalIni4;
  CvPoint verticalFin4;
    
  // Linea derecha area de pateo
  CvPoint verticalIni5;
  CvPoint verticalFin5;
   
public:
  
  void CamAbajoMedio(){

    moverCamara(abajoMedio);

    RaspiCamCvCapture * camara = raspiCamCvCreateCameraCapture(0);
    this.imgOriginal = raspiCamCvQueryFrame(camara);
    mostrarImagen();

    this.enZonaPateo = false;
  }

  void mostrarImagen(){
    Size sizeImgOrig = this.imgOriginal.size();
    imgLines = Mat::zeros(  sizeImgOrig , CV_8UC3 );

    // Puntos para seccionar la imagen
    verticalIni = cvPoint(imgLines.size().width*3/12,0);
    verticalFin =
      cvPoint(imgLines.size().width*3/12,(imgLines.size().height)*5/6);
 
    verticalIni2 = cvPoint(imgLines.size().width*2/3,0);
    verticalFin2 =
      cvPoint(imgLines.size().width*2/3,imgLines.size().height*5/6);

    horizontalIni = cvPoint(0,imgLines.size().height*5/6);
    horizontalFin =
      cvPoint(imgLines.size().width,imgLines.size().height*5/6);

    verticalIni3 = 
      cvPoint(imgLines.size().width*3/12,imgLines.size().height*5/6);
    verticalFin3 =
      cvPoint(imgLines.size().width*3/12,imgLines.size().height);

    verticalIni4 = 
      cvPoint(imgLines.size().width*5/12,imgLines.size().height*5/6);
    verticalFin4 =
      cvPoint(imgLines.size().width*5/12,imgLines.size().height);
    
    verticalIni5 = 
      cvPoint(imgLines.size().width*2/3,imgLines.size().height*5/6);
    verticalFin5 =
      cvPoint(imgLines.size().width*2/3,imgLines.size().height);

    // Dibujar division de la pantalla
    line(imgLines, horizontalIni, horizontalFin, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni, verticalFin, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni2, verticalFin2, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni3, verticalFin3, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni4, verticalFin4, cvScalar(0,255,0), 1);
    line(imgLines, verticalIni5, verticalFin5, cvScalar(0,255,0), 1);

    imgOriginal = imgOriginal + imgLines;
    imshow("Original", imgOriginal);
    waitKey(10);
    // Cerrar la camara ??
  }

bool irZonaPateo(){
  int maxGiros = 5; // Numero de veces a girar sin ver la pelota
  int vuelta = 1;

  while(vuelta < maxGiros){
    bool pelotaAlaVista = ubicarPelota();
    if(pelotaAlaVista && this.enZonaPateo) return true;
    if(! pelotaAlaVista) {
      vuelta++;
      hacerGiro();
    }
  }
  // Alcanzó el numero max de giros sin encontrar pelota
  return false;
}

// Devuelve true si ubicó la pelota en alguna camara
// Devuelve false si no la vio en ninguna camara 
bool ubicarPelota(){

  if (deteccionPelota.esVisible(this.imgOriginal)){
    this.enZonaPateo = false;
    switch (cuadrantePelota()){ 
    case 1: // Adelante
      break;
    case 2: // Derecha
      break;
    case 3: // Izquierda
      break;
    case 4: // Izquierda
      break;
    case 5: // Patada Izquierda
      this.enZonaPateo = true ;
      break;
    case 6: //Patada Derecha
      this.enZonaPateo = true ;
      break;
    case 7: // Derecha
      break;
    }
    return true;

  } else {
    CamArribaMedio camArriba = new CamArribaMedio();
    return camArriba.ubicarPelota();
  }

}

int cuadrantePelota(){
  this.posicionPelota= deteccionPelota.obtenerPosicion();

  if (estaEnIzquierda()){
    cuadrantePelota = 1; 
  }elseif(estaEnMedioArriba()){
    cuadrantePelota = 2;
  }elseif(estaEnDerecha()){
    cuadrantePelota = 3;
  }elseif(estaEnPateoIzquierda()){
    cuadrantePelota = 4;
  }elseif(estaEnPateoDerecha()){
    cuadrantePelota = 5;
  }
}

bool estaEnMedioArriba(){
  
  if (posicionPelota.x > verticalIni.x 
      && posicionPelota.x < verticalIni2.x
      && posicionPelota.y < horizontalIni.y ){

    return true;
  }
  return false;
}

bool estaEnDerecha(){
  
  if (posicionPelota.x > verticalIni2.x){
    return true;
  }
  return false;
}

bool estaEnIzquierda(){
  
  if (posicionPelota.x < verticalIni.x){
    return true;
  }
  return false;
}

bool estaEnPateoIzquierda(){
  
  if (posicionPelota.x > verticalIni3.x 
      && posicionPelota.x < verticalIni4.x
      && posicionPelota.y > horizontalIni.y ){

    return true;
  }
  return false;
}

bool estaEnPateoDerecha(){
  
  if (posicionPelota.x > verticalIni4.x 
      && posicionPelota.x < verticalIni5.x
      && posicionPelota.y > horizontalIni.y ){

    return true;
  }
  return false;
}

};





