#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;

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
    
    namedWindow("Imagen Original", CV_WINDOW_AUTOSIZE);// Crea una ventana
    imshow("Imagen Original", image);                      // Muestra nuestra imagen dentro de esta.
    waitKey(0);                                 // Espera por una tecla
    return 0;


}

