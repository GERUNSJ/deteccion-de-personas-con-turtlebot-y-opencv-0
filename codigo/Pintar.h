/* 
 * File:   Pintar.h
 * Author: fabricio
 *
 * Created on 12 de abril de 2014, 11:46
 */
//#include <vector>
#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "stdlib.h"
#ifndef PINTAR_H
#define	PINTAR_H
//#include <Pintar.cpp>
namespace pintar
{
    
    //cv::Scalar popo(0,0,255);
   
    class Color
    {
    private:

        cv::Point3_<uchar> color;
        
    public:
        Color();
        ~Color();
        void generocolor();
         Color& operator= (const Color&);
        //int operator!= (const Color&, const Color&);
        cv::Point3_<uchar> devuelvocolor(void);
        void setcolor(cv::Point3_<uchar>);

        Color(cv::Point3_<uchar>);

        //operator cv::Point3_() {return color;} //No anda
    };
    void Pintar(const cv::Mat &src, cv::Mat &dst, std::vector<std::vector<int> > LimiteEObjeto, Color *vectorColor);
    

}


#endif	/* PINTAR_H */

