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
    original = imread(argv[1], 0);   		//El segundo argumento indica que la imagen se leera
    											//tal como viene, tenga los canales que tenga.

    if(! original.data )                       	// Check for invalid input
    {
        cout <<  "No se pudo abrir o encontrar la imagen." << std::endl ;
        return -1;
    }
//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE VENTANAS
 ---------------------------------------------------------------------*/

    namedWindow( "ORIGINAL", WINDOW_AUTOSIZE );	// Create a window for display.
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

    //Mat histograma;
    //Mat histograma_img;
    //Mat histograma_filtrado;


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

    f_histograma(original);




    imshow( "ORIGINAL", original );                   	// Show our image inside it.

    waitKey(0);                                    	// Wait for a keystroke in the window
    return 0;
}


