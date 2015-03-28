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

void suavizar_histograma(Mat& histograma, int ancho_filtro);



void suavizar_histograma(Mat& histograma, int ancho_filtro)
{
	//C++: void blur(InputArray src, OutputArray dst, Size ksize, Point anchor=Point(-1,-1), int border-type=BORDER_DEFAULT )
	blur(histograma, histograma, Size(1,ancho_filtro), Point(-1,-1), BORDER_REFLECT_101);	//Size(columnas,filas)
	//BORDER_REPLICATE supone que los valores de borde se mantienen constantes.
	//BORDER_REFLECT_101 gfedcb|abcdefgh|gfedcba
}



#endif /* SUAVIZAR_HISTOGRAMA_HPP_ */
