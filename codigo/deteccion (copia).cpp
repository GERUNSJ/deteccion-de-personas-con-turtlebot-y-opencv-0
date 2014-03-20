#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


void Sharpen2(const Mat &myImage, Mat &Result)
{
    //CV_Assert(myImage.depth() == CV_8U); // accept only uchar images
    
    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();
    
    
    for (int j= 1; j < myImage.rows - 1; ++j)
    {
            
            const uchar* previous = myImage.ptr<uchar>(j - 1);
            const uchar* current = myImage.ptr<uchar>(j);
            const uchar* next= myImage.ptr<uchar>(j + 1);
            
            uchar* output = Result.ptr<uchar>(j);
            
            for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) 
            {
                *output++ = saturate_cast<uchar>(5 * current[i]- current[i - nChannels] - current[i + nChannels] - previous[i] -next[i]);
                /*o=[0 -1 0
                     -1 5 -1
                     0  -1 0]
                 
                 */
            }
        }
    //Result.row(0).setTo(Scalar(0));
    //Result.row(Result.rows - 1).setTo(Scalar(0));
    //Result.col(0).setTo(Scalar(0));
    //Result.col(Result.cols - 1).setTo(Scalar(0));
}

void Sharpen(const Mat &myImage, Mat &Result)
{
   //CV_Assert(myImage.depth() == CV_8U); // accept only uchar images
    
    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();
    
    for (int j= 1; j < myImage.rows - 1; ++j)
    {
            
            const int* previous = myImage.ptr<int>(j - 1);
            const int* current = myImage.ptr<int>(j);
            const int* next= myImage.ptr<int>(j + 1);
            
            int* output = Result.ptr<int>(j);
            
            for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) 
            {
                if(current[i]>5000)
                {
                    *output++ =0;
                }
                else
                {
                *output++ = saturate_cast<int>(-4 * current[i]+ current[i - nChannels] + current[i + nChannels] + previous[i] + next[i]);
                }
                /*o=[0 -1 0
                     -1 5 -1
                     0  -1 0]
                 
                 */
            }
        }
    //Result.row(0).setTo(Scalar(0));
    //Result.row(Result.rows - 1).setTo(Scalar(0));
    //Result.col(0).setTo(Scalar(0));
    //Result.col(Result.cols - 1).setTo(Scalar(0));
}

void filter(const Mat &myImage, Mat &Result)
{
        //contruccion del kernel
    const int kernel_size=3;
    float a=-1 ,b=0 ,c=1 ,d=-1 ,e=1 ,f=0 ,g=0 ,h=0 ,i=0;
    Mat kernel;
    //int m[3][3]={{0,0,0},{0,1,0},{0,0,0}};
    float m[kernel_size][kernel_size]={
        {a, b, c}, 
        {d, e, f}, 
        {g, h, i}};
    
    
    //kernel = Mat(kernel_size, kernel_size, CV_8U, m)/9;
    //kernel = Mat(kernel_size, kernel_size, CV_8U, m);
    
    //definicion de los parametros del filtro
    Point anchor = Point( -1, -1 );;
    double delta=0;
    int ddepth=-1;
    
    //ddepth = -1/CV_16S/CV_32F/CV_64F;
    //
    
    
    //defino el kernel 
    kernel = Mat(3,3, CV_32F, m);
        
    /// Apply filter
    filter2D(myImage, Result, ddepth , kernel, anchor, delta, BORDER_DEFAULT );
}

int main(int argc, char** argv)
{
    if(argc!=2)
    {
        cout<<" Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }
    
    Mat image;
    image=imread(argv[1], CV_LOAD_IMAGE_COLOR); // Lectura del archivo
    
    if(!image.data)                             // Chequea que sea un dato valido
    {
        cout<<"no se puede abrir o encontrar la imagen"<< endl;
        return -1;
    }
    Mat Resultado;
    Mat Filtrada;
    Mat enfoque;
    Mat Casero;
    Sharpen2(image,enfoque);
    filter(enfoque, Filtrada);
    Sharpen(Filtrada, Resultado);
    //filter(image, Filtrada);
    Sharpen(image,Casero);
    
    namedWindow("Imagen Original", CV_WINDOW_AUTOSIZE);// Crea una ventana
    imshow("Imagen Original", image);                      // Muestra nuestra imagen dentro de esta.
    namedWindow("Imagen filtro linea 1", CV_WINDOW_AUTOSIZE);// Crea una ventana con mejor enfoque
    imshow("Imagen filtro linea 1", Filtrada);                      // Muestra nuestra imagen enfocada dentro de esta.
    namedWindow("Imagen Realce Linea", CV_WINDOW_AUTOSIZE);// Crea una ventana de Realce Linea
    imshow("Imagen Realce Linea", Resultado);                      // Muestra nuestra imagen Realzada dentro de esta.
    namedWindow("Imagen filtro Casero", CV_WINDOW_AUTOSIZE);// Crea una ventana de Realce Linea
    imshow("Imagen filtro Casero", Casero);               
    waitKey(0);                                 // Espera por una tecla
    return 0;


}


