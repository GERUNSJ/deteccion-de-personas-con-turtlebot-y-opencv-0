/*
 * suavizar_histograma.hpp
 *
 *  Created on: 01/05/2014
 *      Author: pablo
 */

#ifndef SUAVIZAR_HISTOGRAMA_HPP_
#define SUAVIZAR_HISTOGRAMA_HPP_

using namespace cv;
using namespace std;

//#include <suavizar_histograma.cpp>

void suavizar_histograma(Mat& histograma);



void suavizar_histograma(Mat& histograma)
{
	//C++: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int border-type=BORDER_DEFAULT )
	blur(histograma, histograma, Size(1,5), Point(-1,-1), BORDER_REPLICATE);	//Size(columnas,filas)
}



#endif /* SUAVIZAR_HISTOGRAMA_HPP_ */
