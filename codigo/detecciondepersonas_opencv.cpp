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
#include <suavizar_histograma.hpp>
#include <valles.hpp>
#include <Pintar.hpp>
#include <time.h>
#include <cstdio>


using namespace cv;
using namespace std;

//--------------------------------------------------------------
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
	srand(time(NULL));
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
        cout <<  "\nNo se pudo abrir o encontrar la imagen." << std::endl ;
        return -1;
    }

    string tipo = type2str(original.type());
    cout << "\nLa imagen abierta es del tipo " << tipo << "\n" ;

    //Conversión a un canal
    if(original.channels() != 1)
    {
    	cvtColor(original, original, CV_RGB2GRAY);
    }
//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE VENTANAS
 ---------------------------------------------------------------------*/

    namedWindow( "ORIGINAL", WINDOW_AUTOSIZE );	// Create a window for display.
    namedWindow( "NORMALIZADA", WINDOW_AUTOSIZE);
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA_SUAVIZADO", WINDOW_AUTOSIZE);
    namedWindow( "PICOS_HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "PINTADA", CV_WINDOW_AUTOSIZE );

//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE MATRICES
 ---------------------------------------------------------------------*/

    Mat normalizada;
    Mat histograma;
    Mat histograma_suavizado;
    Mat pintada;
    Mat original_color;





//---------------------------------------------------------------------
//---------------------------------------------------------------------



/*---------------------------------------------------------------------
 * 				NORMALIZACIÓN
 ---------------------------------------------------------------------*/

/*
    cout << "\n Antes de la normalizacion\n";

    long int i = 0;
    long int j = 0;
    long int nn = 0;
    int a = original.type();
    cout << "\n el tipo es " << original.type();

	for( i = 0; i < original.rows; i++)
	{
		for (j = 0; j < original.cols; j++)
			{
				if(original.at<int>(i,j)!=0)
				{
				//printf("%ld  ",(long int)original.at<int>(i));
				nn++;
				}
			}
	}
	printf("\n\n i*j = %ld\n\n",i*j);
	printf("\nHay %ld valores no nulos.\n\n",nn);
*/

    cout << "\n\nANTES DE NORMALIZAR:\n";
    f_histograma_log(original,histograma);
    mostrar_histograma(histograma, (char*)"HISTOGRAMA");

    double minVal;
    double maxVal=0;

    if(original.depth() == CV_8U)
    {
        //normalize(original, normalizada, 0, 255, NORM_MINMAX, -1);
        normalizada = original.clone();
        minMaxLoc(normalizada, &minVal, &maxVal, NULL, NULL, Mat() );
        cout << "\nMin val es: " << minVal;
        cout << "\nMax val es: " << maxVal;
        cout << "\n255.0/(maxVal - minVal) es : " << 255.0/(maxVal - minVal);
        //normalizada = normalizada - minVal;
        //normalizada = normalizada * (255.0/(maxVal - minVal));
        normalizada.convertTo(normalizada,CV_8UC1,255.0/(maxVal - minVal), -minVal * 255.0/(maxVal - minVal));
        //C++: void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point*
        //maxLoc=0, InputArray mask=noArray())

    }
    else if (original.depth() == CV_16U)
    {
        normalize(original, normalizada, 0, 65535, NORM_MINMAX, -1);
    }
    //original.convertTo(normalizada,CV_16UC1,65535.0/(10000 - 0), -0 * 65535.0/(10000 - 0));
    imshow("NORMALIZADA",normalizada);
    waitKey(0);

    if (original.depth() == CV_16U)
    {
        normalize(original, normalizada, 0, 65535, NORM_MINMAX, -1);
        //Conversión a 8 bits:
        normalizada.convertTo(normalizada,CV_8UC1,255.0/65535, -0);

    }
    imshow("NORMALIZADA",normalizada);



//---------------------------------------------------------------------
//---------------------------------------------------------------------



/*---------------------------------------------------------------------
 * 				NORMALIZACIÓN
 ---------------------------------------------------------------------*/


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

    cout << "\n\nDESPUES DE NORMALIZAR: \n";

    f_histograma_log(normalizada,histograma);

    /*
    for(int i=1;i<histograma.rows-1;i++)
    {
    	if ((histograma.at<float>(i) == 0) && (histograma.at<float>(i) == histograma.at<float>(i+1)))
    	{
    		histograma.at<float>(i) = histograma.at<float>(i-1);
    	}
    }
    */

    mostrar_histograma(histograma, (char*)"HISTOGRAMA");


/*---------------------------------------------------------------------
 * 				SUAVIZADO DE HISTOGRAMA
 ---------------------------------------------------------------------*/

    histograma_suavizado = histograma.clone();
    suavizar_histograma(histograma_suavizado, 9);
    suavizar_histograma(histograma_suavizado, 5);
    suavizar_histograma(histograma_suavizado, 5);
    suavizar_histograma(histograma_suavizado, 3);
    mostrar_histograma(histograma_suavizado, (char*)"HISTOGRAMA_SUAVIZADO");

//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				VALLES
 ---------------------------------------------------------------------*/

    //std::vector<int> valles;
    std::vector< std::vector<int> > pares;

	/*for(int i=0; i < histograma_suavizado.rows ; i++)	//Del 1 al 254
	{
		cout << i << '=' << histograma_suavizado.at<float>(i) << "   ";
	}
	cout << "\n";*/

    //valles = encontrar_valles(histograma_suavizado);
    encontrar_valles(histograma_suavizado , pares);

//---------------------------------------------------------------------
//---------------------------------------------------------------------

    cvtColor(normalizada, original_color, CV_GRAY2BGR);
    pintada=original_color;

    string tipo3 = type2str(original_color.type());
    cout << "\n La imagen original color es del tipo " << tipo3 << "\n" ;
    imshow( "PINTADA", original_color );
    waitKey(0);
    pintar::Pintar(original_color, pintada, pares);

    imshow( "PINTADA", pintada );


    imshow( "ORIGINAL", original );                   	// Show our image inside it.

    waitKey(0);                                    	// Wait for a keystroke in the window
    return 0;
}


