//#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Pintar.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 

uchar d;
namespace pintar
{
    void Pintar(const cv::Mat &src, cv::Mat &dst, std::vector<std::vector<int> > LimiteEObjeto, Color *vectorColor)
    {        
        int dim = 256;
        cv::Mat lut(1, dim, CV_8UC(dst.channels()));
        for (int i = 0; i < 256; i++) {
            lut.at<cv::Vec3b>(i) = cv::Point3_<uchar>(0, 0,0);
        }
        for(int j=0; j< LimiteEObjeto.size();j++) {
            Color Objeto;
            //Objeto = new Color;
            Objeto.generocolor();
            for(int i= LimiteEObjeto[j][0]; i < LimiteEObjeto[j][1];i++)
            {
                
                lut.at<cv::Vec3b>(i)=Objeto.devuelvocolor();
            }
            //delete Objeto;
           // std::cout<<  lut.at<cv::Vec3b>(i) << std::endl;
            vectorColor[j] = Objeto;
            Objeto.~Color();
        }
        //delete Objeto;
        cv::LUT(src,lut,dst,0);
    }
    
    Color::Color()
    {
    
    }
    Color& Color::operator= (const Color& cd){
        //if (*this != cd)
            color = cd.color;
        return *this;
    }/*
    int Color::operator!= (const Color& c1, const Color& c2){
        if(c1.color == c2.color)
            return 0;
        else
            return 1;
    }*/
    
    cv::Point3_<uchar> Color::devuelvocolor()
    {
        return color;
    }
    void Color::generocolor()
    {
       
        color = cv::Point3_<uchar>(rand()%255 , rand()%255, rand()%255);
    }
    Color::~Color()
    {
        // destruir el numero complejo...
    }

}
