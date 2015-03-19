/*
 * histograma.hpp
 *
 *  Created on: 10/04/2014
 *      Author: pablo
 */
//#include <iostream>

#include <cstdio>

#ifndef HISTOGRAMA_HPP_
#define HISTOGRAMA_HPP_

using namespace cv;
using namespace std;

#define V_HIST_ANCHO	640		//El ancho de la ventana del histograma.
#define V_HIST_ALTO		480

//------------------------------------------------------------------------------

void f_histograma(const Mat& img, Mat& hist);
/*	Calcula el histograma de img y lo devuelve en hist. Funciona para imagenes
 * 	de un solo canal, tanto 16UC1 como 8UC1. *
 */
void f_histograma_log(const Mat& img, Mat& hist);
/*	Lo mismo que la anterior, pero en forma logarítmica. Los máximos y mínimos
 *	se preservan (con lo cual sigue sirviendo para la segmentación),
 *	y es más fácil de visualizar.
 *
 */
void mostrar_histograma(const Mat& hist_original, char* nombreventana);
/*	Dibuja el histograma con líneas en una imagen de tamaño definido por las constantes
 * 	V_HIST_ANCHO y V_HIST_ALTO. Antes de dibujar, los histogramas se resizean al tamaño
 * 	de la ventana.
 *
 */

string type2str(int type);

//--------------------------------------------------------------------------------


void f_histograma(const Mat& img, Mat& hist)
{
	// Initialize parameters

	int histSize = 0;		//bin size
    float range16[] = { 0, 65535 }; //255		//Es un arreglo de 2 elementos.
    const float *ranges16[] = { range16 };		//Es un arreglo de punteros?

    float range8[] = { 0, 255 }; //255
    const float *ranges8[] = { range8 };



    if(img.depth() == CV_8U)
    {
    	histSize = 256;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges8, true, false );
    }
    else if(img.depth() == CV_16U)
    {
    	histSize = 65536;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges16, true, false );
    }

    /*
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }*/


/*
    // Calculate histogram
    //Mat hist;
    calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

    //Mostrar valores del histograma en consola.
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }
*/

    string tipo = type2str(hist.type());
    cout << "\nEl histograma es del tipo " << tipo << "\n" ;
    cout << "\n El histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";

    return;

}

//...........................................................................

void f_histograma_log(const Mat& img , Mat& hist)
{
	// Initialize parameters

	int histSize = 0;		//bin size
    float range16[] = { 0, 65535 }; //255		//Es un arreglo de 2 elementos.
    const float *ranges16[] = { range16 };		//Es un arreglo de punteros?

    float range8[] = { 0, 255 }; //255
    const float *ranges8[] = { range8 };



    if(img.depth() == CV_8U)
    {
    	histSize = 256;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges8, true, false );
    }
    else if(img.depth() == CV_16U)
    {
    	histSize = 65536;
        calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges16, true, false );
    }




/*

   // Calculate histogram
    //Mat hist;
    //calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

*/



//Logaritmo

    for(int i=0;i<hist.rows;i++)
    {
    	hist.at<float>(i) = log(hist.at<float>(i));
    	if(hist.at<float>(i)<0)hist.at<float>(i)=0;	//satura
    }




/*
    // Show the calculated histogram in command window

    cout << "\ndespues del log" << std::endl;

    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }
*/

/*


    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
    }

    namedWindow( "Result", 1 );
    imshow( "Result", histImage );

    waitKey(0);

*/

    string tipo = type2str(hist.type());
    cout << "\nEl histograma es del tipo " << tipo << "\n" ;
    cout << "\nEl histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";

    return;
}


//------------------------------------------------------------------------------------------------



void mostrar_histograma(const Mat& hist_original, char* nombreventana)
{

    //string tipo = type2str(hist_original.type());
    //cout << "\nEl histograma es del tipo " << tipo << "\n" ;
	Mat hist = hist_original;


    int histSize = V_HIST_ANCHO;
    int i = 0;


/*
    long int nn = 0;
    double suma = 0;


	for( i = 0; i < hist.rows; i++)
	{
		//cout << " "<< hist.at<float>(i);

		if(hist.at<float>(i)!=0)
		{
		//printf("%ld  ",(long int)hist.at<float>(i));
		nn++;
		//cout << " "<< hist.at<float>(i);
		suma += hist.at<float>(i);
		}
	}
	printf("\n\n i = %d\n\n",i);
	printf("\nHay %ld valores no nulos.\n",nn);
	printf("\nSuma es = %f\n\n",suma);
*/



/*

	double min = 0;
	double max = 0;
	Point maxLoc;
	Point minLoc;
	 //C++: void minMaxLoc(InputArray src, double* minVal, double* maxVal=0, Point* minLoc=0, Point* maxLoc=0, InputArray mask=noArray())
	cv::minMaxLoc(hist, &min, &max, &minLoc , &maxLoc);
	cout << "\nAntes del resize" << "\nMax = " << max << " en maxLoc = " << maxLoc << "\n";
	cout << "\nAntes del resize" << "\nMin = " << min << " en minLoc = " << minLoc << "\n";

*/




	if (hist.rows > V_HIST_ANCHO)
	{
		resize(hist, hist, Size(1,V_HIST_ANCHO), 0 ,0, INTER_AREA);		//Interpolación por área para reducir la imagen. Se come el valor en 0 pero no lo necesitamos..
		//cout << "\nAhora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
	}
	else if(hist.rows < V_HIST_ANCHO)
	{
		resize(hist, hist, Size(1,V_HIST_ANCHO), 0 ,0, INTER_LINEAR);	//Interpolación lineal para agrandar la imagen.
		//cout << "\nAhora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
	}



/*

    if (hist.rows > 256)
    {
    	histSize = 1024;
      	//C++: void resize(InputArray src, OutputArray dst, Size dsize, double fx=0, double fy=0, int interpola-
    	//tion=INTER_LINEAR )
    	resize(hist, hist, Size(1,1024), 0 ,0, INTER_AREA);
        cout << "\n Ahora el histograma tiene " << hist.rows << " filas y " << hist.cols << " columnas.\n";
    }
*/


	/*
	cv::minMaxLoc(hist, &min, &max, &minLoc , &maxLoc);
	cout << "\nDespues del resize" << "\nMax = " << max << " en maxLoc = " << maxLoc << "\n";
	cout << "\nDespues del resize" << "\nMin = " << min << " en minLoc = " << minLoc << "\n";
*/



    // Plot the histogram
	//					Tal vez se vería mejor un histograma con barras.

    int hist_w = V_HIST_ANCHO; int hist_h = V_HIST_ALTO;
    int bin_w = cvRound( (double) hist_w/histSize );
   // cout << "\nBin_w = " << bin_w << "\n";

    Mat histImage( hist_h, hist_w, CV_8UC3, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 0, 0, 255), 1, 8, 0  );
    }

    //namedWindow( "Result", 1 );
    imshow( nombreventana, histImage );

    waitKey(0);
}

#endif /* HISTOGRAMA_HPP_ */




/* ORIGINAL
 *
 * void f_histograma_log(const Mat& img )
{
    // Initialize parameters
    int histSize = 256;    // bin size
    float range[] = { 0, 65535 };
    const float *ranges[] = { range };

    // Calculate histogram
    Mat hist;
    calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

    cout << "zsdsdfgsrfghdfh" << endl;

    cout << "\nantes del log" << endl;
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }


//Logaritmo
    for(int i=0;i<hist.rows;i++)
    {
    	hist.at<float>(i) = log(hist.at<float>(i));
    	if(hist.at<float>(i)<0)hist.at<float>(i)=0;	//satura
    }
//

    // Show the calculated histogram in command window

    cout << "\ndespues del log" << endl;

    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }

    // Plot the histogram
    int hist_w = 512; int hist_h = 400;
    int bin_w = cvRound( (double) hist_w/histSize );

    Mat histImage( hist_h, hist_w, CV_8UC1, Scalar( 0,0,0) );
    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < histSize; i++ )
    {
      line( histImage, Point( bin_w*(i-1), hist_h - cvRound(hist.at<float>(i-1)) ) ,
                       Point( bin_w*(i), hist_h - cvRound(hist.at<float>(i)) ),
                       Scalar( 255, 0, 0), 2, 8, 0  );
    }

    namedWindow( "Result", 1 );
    imshow( "Result", histImage );

    waitKey(0);
    return;
}
*/

