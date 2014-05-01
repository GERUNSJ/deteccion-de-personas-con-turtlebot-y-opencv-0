/* 
 * File:   Pintar.h
 * Author: fabricio
 *
 * Created on 12 de abril de 2014, 11:46
 */
#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#ifndef PINTAR_H
#define	PINTAR_H
namespace pintar
{
    void Pintar(const cv::Mat src, std::vector<std::vector<int> > LimiteEObjeto);
    cv::Scalar popo(0,0,255);
   
    class Color
    {
    private:

        cv::Scalar color;
        
    public:
        Color();
        ~Color();
        cv::Scalar generocolor(void);
        void setcolor(cv::Scalar);

        Color(cv::Scalar);
    };
    

}


#endif	/* PINTAR_H */

