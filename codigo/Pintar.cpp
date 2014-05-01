#include <vector>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include "Pintar.h"

namespace pintar
{
    void Pintar(const cv::Mat src,const cv::Mat dst, std::vector<std::vector<int> > LimiteEObjeto)
    {        
        int dim(256);
        cv::Mat lut(1, &dim, CV_8UC(dst.channels()));
        for (int i = 0; i < 256; i++) {
            lut.at<cv::Scalar>(i) = cv::Scalar(0, 0, 0);
        }
        for(int j; j< LimiteEObjeto.size();j++) {
            Color Objeto;
            for(int i= LimiteEObjeto[j][0]; i < LimiteEObjeto[j][1];i++)
            {
                lut.at<cv::Scalar>(i)=Objeto.generocolor();
            }            
        }
        cv::LUT(src,lut,dst);


//        
//        for(int i=0; i < LimiteEObjeto.size();i++)
//        {
//            Color objeto1;
//            Color objeto2;
//            for(int j=0;j<= src.rows;j++)
//            {
//                for(int k=0; k<= src.cols;k++)
//                {
//                    if( (src[j][k]>LimiteEObjeto[i][0]) || (src[j][k]<LimiteEObjeto[i][]) )
//                    {
//                        if()
//                        
//                        dst[j][k]= objeto1.generocolor();
//                        
//                    }
//                }
//            }
//        }
    }
    
    Color::Color()
    {
        cv::RNG rng(65536);
        color =(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
    }
    
    cv::Scalar Color::generocolor()
    {
        return color;
    }
    Color::~Color()
    {
        // destruir el numero complejo...
    }

}
