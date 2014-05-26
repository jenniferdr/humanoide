#include <iostream>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace cv;
using namespace std;

int main (int argc, char ** argv) {

  // capturar la camara en vivo 
  VideoCapture camara(0);  
  
  if (!camara.isOpened()) 
    {
      cout << "No se puedo abrir la camara" << endl;
      return -1;
    }

  // Crea una nueva ventana
  namedWindow("video",CV_WINDOW_AUTOSIZE);
  
  /* Para calcular el HUE, Saturacion y Valor
   * de la pelota
   */

  int iLowH = 0;
  int iHighH = 94; // Color especifico a buscar
    
  int iLowS = 75; 
  int iHighS = 255;
    
  int iLowV = 78;
  int iHighV = 255;
      
  // Crear un control para cambiar la HUE (0 - 179)
  createTrackbar("LowH", "video", &iLowH, 179); //Hue (0 - 179)
  createTrackbar("HighH", "video", &iHighH, 179);
    
  // Crear un control para cambiar la saturacion (0-255)
  createTrackbar("LowS", "video", &iLowS, 255); //Saturation (0 - 255)
  createTrackbar("HighS", "video", &iHighS, 255);
    
  // Crear un control para cambiar el valor (0-255)
  createTrackbar("LowV", "video", &iLowV, 255);//Value (0 - 255)
  createTrackbar("HighV", "video", &iHighV, 255);
  
  namedWindow("video1",CV_WINDOW_AUTOSIZE);
  /* Para calcular el HUE, Saturacion y Valor
   * de la Arqueria
   */

  int ALowH = 96 ;
  int AHighH = 120; // Color especifico a buscar
    
  int ALowS = 116; 
  int AHighS = 199;
    
  int ALowV = 71;
  int AHighV = 255;
  
  // Crear un control para cambiar la HUE (0 - 179)
  createTrackbar("LowH", "video1", &ALowH, 179); //Hue (0 - 179)
  createTrackbar("HighH", "video1", &AHighH, 179);
    
  // Crear un control para cambiar la saturacion (0-255)
  createTrackbar("LowS", "video1", &ALowS, 255); //Saturation (0 - 255)
  createTrackbar("HighS", "video1", &AHighS, 255);
    
  // Crear un control para cambiar el valor (0-255)
  createTrackbar("LowV", "video1", &ALowV, 255);//Value (0 - 255)
  createTrackbar("HighV", "video1", &AHighV, 255);
   
  //Un cuadro temporal
  Mat imgTmp;
  camara.read(imgTmp); 

  int iLastX = -1; 
  int iLastY = -1;
  
  while (1)
    {
      Mat cuadro;
      Mat imgOriginal;
      //Create a black image with the size as the camera output
      Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );;
      
      bool bSuccess = camara.read(imgOriginal); // leer un cuadro del video
      
      if (!bSuccess) 
	{
	  cout << "Cannot read a frame from video stream" << endl;
	  break;
	}
      Mat imgHSV;
     
      //Convertir el cuadro de BGR a HSV
      cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); 
      Mat imgFiltro;
      Mat imgArqueria;
      inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgFiltro); //Threshold the image
    
      //morphological opening (removes small objects from the foreground)
      erode(imgFiltro, imgFiltro, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
      dilate( imgFiltro,imgFiltro, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
     
      //morphological closing (removes small holes from the foreground)
      dilate( imgFiltro, imgFiltro, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
      erode(imgFiltro, imgFiltro, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

      /********* PARA LA ARQUERIA ********/
      inRange(imgHSV, Scalar(ALowH, ALowS, ALowV), Scalar(AHighH, AHighS, AHighV), imgArqueria); //Threshold the image
	  
      //morphological opening (removes small objects from the foreground)
      erode(imgArqueria, imgArqueria, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
      dilate( imgArqueria,imgArqueria, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
     
      //morphological closing (removes small holes from the foreground)
      dilate( imgArqueria, imgArqueria, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) ); 
      erode(imgArqueria, imgArqueria, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
     
      /********** Para PElota ******/
      Moments pMomentos = moments(imgFiltro);
      double dM01 = pMomentos.m01;
      double dM10 = pMomentos.m10;
      double dArea = pMomentos.m00;
      /********* Para Arqueria *****/
      Moments AMomentos = moments(imgArqueria);
      double AM01 = AMomentos.m01;
      double AM10 = AMomentos.m10;
      double AArea = AMomentos.m00;

      if (dArea > 10000)
	{
	  
	  int posX = dM10 / dArea;
	  int posY = dM01 / dArea;        
	  
	  int posX1 = AM10 / AArea;
	  int posY1 = AM01 / AArea;        
	  
	  if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
	    {
	      line(imgLines, cvPoint(00,(imgLines.size().height)/2), cvPoint(imgLines.size().width,(imgLines.size().height)/2), cvScalar(0,255,0), 1);
	      
	      //	line(imgLines, cvPoint(00,(imgLines.size().height)/2), cvPoint(imgLines.size().width,(imgLines.size().height)/2), cvScalar(0,255,0), 1);
	      
	      cout <<  imgTmp.size().height<< endl;   	     
	      circle(imgLines,Point2f(posX,posY),50,Scalar(255,0,0),1,CV_AA,0);
	      circle(imgLines,Point2f(posX1,posY1),50,Scalar(255,0,0),1,CV_AA,0);
	    }
	  iLastX = posX;
	  iLastY = posY;
	}
      imshow("Thresholded Image", imgFiltro); //show the thresholded image
      imshow("Thresholded1 Image", imgArqueria); //show the thresholded image
      
      imgOriginal = imgOriginal + imgLines;
      imshow("Original", imgOriginal); //show the original image
      
      if (waitKey(30) == 27) 
	{
	  cout << "esc key is pressed by user" << endl;
	  break; 
	}
    }
  return 0;
  
}


