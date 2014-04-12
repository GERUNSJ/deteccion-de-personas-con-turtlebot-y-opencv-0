//============================================================================
// Name        : detecciondepersonas_opencv.cpp
// Author      : Fabricio Emder - Pablo Aguado
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <histograma.hpp>

using namespace cv;
using namespace std;

//void f_filtrado_histograma(const Mat& histograma, Mat& histograma_filtrado);
//void f_histograma(const Mat& img);


string type2str(int type) {
  string r;

  uchar depth = type & CV_MAT_DEPTH_MASK;
  uchar chans = 1 + (type >> CV_CN_SHIFT);

  switch ( depth ) {
    case CV_8U:  r = "8U"; break;
    case CV_8S:  r = "8S"; break;
    case CV_16U: r = "16U"; break;
    case CV_16S: r = "16S"; break;
    case CV_32S: r = "32S"; break;
    case CV_32F: r = "32F"; break;
    case CV_64F: r = "64F"; break;
    default:     r = "User"; break;
  }

  r += "C";
  r += (chans+'0');

  return r;
}
//----------------------------------------

int main( int argc, char** argv )
{
/*---------------------------------------------------------------------
 * 				APERTURA DE LA IMAGEN
 ---------------------------------------------------------------------*/
    if( argc != 2)
    {
     std::cout << "Uso: detecciondepersonas_opencv nombredeimagen" << std::endl;
     return -1;
    }

    Mat original;
    original = imread(argv[1], -1);   		//El segundo argumento indica que la imagen se leera
    											//tal como viene, tenga los canales que tenga.

    if(! original.data )                       	// Check for invalid input
    {
        cout <<  "No se pudo abrir o encontrar la imagen." << std::endl ;
        return -1;
    }

    string tipo = type2str(original.type());
    cout << "La imagen abierta es del tipo " << tipo << "\n" ;
//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE VENTANAS
 ---------------------------------------------------------------------*/

    namedWindow( "ORIGINAL", WINDOW_AUTOSIZE );	// Create a window for display.
    namedWindow( "NORMALIZADA", WINDOW_AUTOSIZE);
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "PICOS_HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );

//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE MATRICES
 ---------------------------------------------------------------------*/

    Mat normalizada;
    //Mat histograma;
    //Mat histograma_img;
    //Mat histograma_filtrado;


//---------------------------------------------------------------------
//---------------------------------------------------------------------

/*---------------------------------------------------------------------
 * 				NORMALIZACIÓN
 ---------------------------------------------------------------------*/

    normalize(original, normalizada, 0, 65535, NORM_MINMAX, -1);
    //original.convertTo(normalizada,CV_16UC1,65535.0/(10000 - 0), -0 * 65535.0/(10000 - 0));
    imshow("NORMALIZADA",normalizada);


//---------------------------------------------------------------------
//---------------------------------------------------------------------
/*---------------------------------------------------------------------
 * 				--
 ---------------------------------------------------------------------*/
/*	histograma
 * 	ecualización
 * 	filtrado de histograma
 * 	detección de picos
 * 	umbralización
 * 	comparación con caja de proporciones y/x
 *
 */

 //   f_histograma(original, histograma);


  //  f_filtrado_histograma(histograma, histograma_filtrado);

    f_histograma(normalizada);




    imshow( "ORIGINAL", original );                   	// Show our image inside it.

    waitKey(0);                                    	// Wait for a keystroke in the window
    return 0;
}


