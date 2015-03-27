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
#include <cstdio>
#include <vector>
#include "valles.hpp"
#include <cstdlib>
#include <Pintar.h>
#include <stdlib.h> 
#include <time.h> 

using namespace cv;
using namespace std;

//--------------------------------------------
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
     cout << "Uso: detecciondepersonas_opencv nombredeimagen" << endl;
     return -1;
    }

    Mat original = imread(argv[1], -1);   		//El segundo argumento indica que la imagen se leera
    original.convertTo(original, CV_8UC1, 255.0/65535,0);											//tal como viene, tenga los canales que tenga.

    if(! original.data )                       	// Check for invalid input
    {
        cout <<  "\nNo se pudo abrir o encontrar la imagen." << endl ;
        return -1;
    }

    string tipo = type2str(original.type());
    cout << "La imagen abierta es del tipo " << tipo << "\n" ;
//    if(original.channels()!= 1)
//        cvtColor(original,original,CV_RGB2GRAY);
//---------------------------------------------------------------------
//---------------------------------------------------------------------


/*---------------------------------------------------------------------
 * 				CREACIÓN DE VENTANAS
 ---------------------------------------------------------------------*/

    namedWindow( "ORIGINAL", CV_WINDOW_AUTOSIZE );	// Create a window for display.
    namedWindow( "NORMALIZADA", WINDOW_AUTOSIZE);
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "PICOS_HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
    namedWindow( "HISTOGRAMA", WINDOW_AUTOSIZE );
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
    cvtColor(original, original_color, CV_GRAY2BGR);
    pintada=original_color.clone();

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
    
          imshow( "ORIGINAL", original ); 
         waitKey(0);
         
         vector < vector<int> > hist_value;
         srand(time(NULL)); 
    // Pintura
         
    
    /*vector < vector<int> > hist_value;
    vector<int> valor;
    valor.push_back(180);
    valor.push_back(255);
    hist_value.push_back(valor);
    vector<int> valor1;
    valor1.push_back(100);
    valor1.push_back(180);
    hist_value.push_back(valor1);
    vector<int> valor2;
    valor2.push_back(50);
    valor2.push_back(100);
    hist_value.push_back(valor2);
    vector<int> valor3;
    valor3.push_back(5);
    valor3.push_back(50);
    hist_value.push_back(valor3);
    
         */

    

    cout << "\n\nANTES DE NORMALIZAR:\n";
    f_histograma_log(original,histograma);
    mostrar_histograma(histograma, (char*)"HISTOGRAMA");


    if(original.depth() == CV_8U)
    {
        normalize(original, normalizada, 0, 255, NORM_MINMAX, -1);
    }
    else if (original.depth() == CV_16U)
    {
        normalize(original, normalizada, 0, 65535, NORM_MINMAX, -1);
    }
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

    //f_histograma(normalizada);
  cout << "\n\nDESPUES DE NORMALIZAR: \n";

    //f_histograma_log(normalizada,histograma);
  f_histograma(normalizada,histograma);
    mostrar_histograma(histograma, (char*)"HISTOGRAMA");


/*---------------------------------------------------------------------
 * 				SUAVIZADO DE HISTOGRAMA
 ---------------------------------------------------------------------*/

    histograma_suavizado = histograma;
    suavizar_histograma(histograma_suavizado,15);
    suavizar_histograma(histograma_suavizado, 9);
    //suavizar_histograma(histograma_suavizado, 9);
    mostrar_histograma(histograma_suavizado, (char*)"HISTOGRAMA_SUAVIZADO");

    
//---------------------------------------------------------------------
    encontrar_valles(histograma_suavizado, hist_value);
//---------------------------------------------------------------------

    string tipo3 = type2str(original_color.type());
    cout << "\n La imagen original color es del tipo " << tipo3 << "\n" ;
    pintar::Pintar(original_color, pintada, hist_value);
    
    string tipo2 = type2str(pintada.type());
    cout << "\n La imagen pintada es del tipo " << tipo2 << "\n" ;
    
    imshow("PINTADA", pintada);
    waitKey(0);


    imshow( "ORIGINAL", original );                   	// Show our image inside it.

    waitKey(0);                                    	// Wait for a keystroke in the window
    return 0;
    
}


