//============================================================================
// Name        : detecciondepersonas_opencv.cpp
// Author      : Fabricio Emder - Pablo Aguado
// Version     :
// Copyright   : Your copyright notice
// Description :
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

f_filtrado_histograma(const Mat& histograma, Mat& histograma_filtrado);
f_histograma(const Mat& img, Mat& histograma);

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

    cv::Mat original;
    original = cv::imread(argv[1], -1);   		//El segundo argumento indica que la imagen se leera
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

    cv::namedWindow( "ORIGINAL", cv::WINDOW_AUTOSIZE );	// Create a window for display.
    cv::namedWindow( "HISTOGRAMA", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "PICOS_HISTOGRAMA", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "HISTOGRAMA", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "HISTOGRAMA", cv::WINDOW_AUTOSIZE );
    cv::namedWindow( "HISTOGRAMA", cv::WINDOW_AUTOSIZE );

//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE MATRICES
 ---------------------------------------------------------------------*/

    cv::Mat histograma;
    cv::Mat histograma_img;
    cv::Mat histograma_filtrado;
    cv::Mat

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

    f_histograma(original, histograma);


    f_filtrado_histograma(histograma, histograma_filtrado);






    imshow( "ORIGINAL", original );                   	// Show our image inside it.

    cv::waitKey(0);                                    	// Wait for a keystroke in the window
    return 0;
}


