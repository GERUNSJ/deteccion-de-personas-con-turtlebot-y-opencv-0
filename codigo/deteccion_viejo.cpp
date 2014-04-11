#include <opencv2/core/core.hpp>
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <iostream>


using namespace cv;
using namespace std;


//threhold-----------------------------------------------------------




int threshold_value = 0;
int threshold_type = 3;
int const max_value = 256;
int const max_type = 4;
int const max_BINARY_value = 256;

Mat src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

void f_histograma(const Mat &fte, Mat &dst) {


    ///
    /// Establish the number of bins
    int histSize = 256;
    /// Set the ranges ( for B,G,R) )
    float range[] = {0, 256};
    const float* histRange = {range};
    bool uniform = true;
    bool accumulate = false;
    /// Compute the histograms:
    calcHist(&fte, 1, 0, Mat(), dst, 1, &histSize, &histRange, uniform, accumulate);


    for (int i = 0; i < 30; i++) {
        dst.at<float>(i) = 0;

    }

    GaussianBlur(dst, dst, Size(5, 5), 0, 0);
    GaussianBlur(dst, dst, Size(5, 5), 0, 0);
    // Draw the histograms
    int hist_w = 512;
    int hist_h = 400;
    int bin_w = cvRound((double) hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    /// Normalize the result to [ 0, histImage.rows ]
    normalize(dst, dst, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(dst.at<float>(i - 1))),
                Point(bin_w * (i), hist_h - cvRound(dst.at<float>(i))),
                Scalar(255, 0, 0), 1, 8, 0);
    }

    /// Display
    namedWindow("calcHist Demo", CV_WINDOW_AUTOSIZE);
    imshow("calcHist Demo", histImage);

}

void Threshold_Demo(int, void*) {
    /* 0:Binary
1:Binary Inverted
2:Threshold Truncated
3:Threshold to Zero
4:Threshold to Zero Inverted
     */
    Mat histograma;
    threshold(src_gray, dst, threshold_value, max_BINARY_value, threshold_type);
    f_histograma(dst, histograma);
    imshow(window_name, dst);
}

void threshold(const Mat &src) {

    src_gray = src;
    /// Convert the image to Gray
    //cvtColor(src, src_gray, CV_RGB2GRAY);
    /// Create a window to display results
    namedWindow(window_name, CV_WINDOW_AUTOSIZE);
    /// Create Trackbar to choose type of Threshold
    createTrackbar(trackbar_type,
            window_name, &threshold_type,
            max_type, Threshold_Demo);
    createTrackbar(trackbar_value,
            window_name, &threshold_value,
            max_value, Threshold_Demo);
    /// Call the function to initialize

    Threshold_Demo(0, 0);

    /// Wait until user finishes program
    while (true) {
        int c;
        c = waitKey(20);
        if ((char) c == 27) {
            break;
        }
    }
}



//------------------------------------------------------------------------------------------

void Sharpen2(const Mat &myImage, Mat &Result) {
    //CV_Assert(myImage.depth() == CV_8U); // accept only uchar images

    Result.create(myImage.size(), myImage.type());
    const int nChannels = myImage.channels();


    for (int j = 1; j < myImage.rows - 1; ++j) {

        const uchar* previous = myImage.ptr<uchar>(j - 1);
        const uchar* current = myImage.ptr<uchar>(j);
        const uchar* next = myImage.ptr<uchar>(j + 1);

        uchar* output = Result.ptr<uchar>(j);

        for (int i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
            *output++ = saturate_cast<uchar>(5 * current[i] - current[i - nChannels] - current[i + nChannels] - previous[i] - next[i]);
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

void Sharpen(const Mat &myImage, Mat &Result) {
    //CV_Assert(myImage.depth() == CV_8U); // accept only uchar images
    cout << "el tipo de la imagen es:" << myImage.type() << "\n";
    cout << "el numero de canales de la imagen es:" << myImage.channels() << "\n";

    Result.create(myImage.size(), myImage.type());
    const uint nChannels = myImage.channels();

    for (int j = 1; j < myImage.rows - 1; ++j) {

        //const int* previous = myImage.ptr<int>(j - 1);
        const uint* current = myImage.ptr<uint>(j);
        //const int* next= myImage.ptr<int>(j + 1);

        uint* output = Result.ptr<uint>(j);
        for (uint i = nChannels; i < nChannels * (myImage.cols - 1); ++i) {
            if (((uint) current[i] > 400000)) {
                *output = 0;
            } else {
                *output = (current[i]);
            }
            *output++;
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

void filter(const Mat &myImage, Mat &Result) {
    //contruccion del kernel
    const int kernel_size = 3;
    float a = -1, b = 0, c = 1, d = -1, e = 1, f = 0, g = 0, h = 0, i = 0;
    Mat kernel;
    //int m[3][3]={{0,0,0},{0,1,0},{0,0,0}};
    float m[kernel_size][kernel_size] = {
        {a, b, c},
        {d, e, f},
        {g, h, i}
    };


    //kernel = Mat(kernel_size, kernel_size, CV_8U, m)/9;
    //kernel = Mat(kernel_size, kernel_size, CV_8U, m);

    //definicion de los parametros del filtro
    Point anchor = Point(-1, -1);
    ;
    double delta = 0;
    int ddepth = -1;

    //ddepth = -1/CV_16S/CV_32F/CV_64F;
    //


    //defino el kernel 
    kernel = Mat(3, 3, CV_16U, m);

    /// Apply filter
    filter2D(myImage, Result, ddepth, kernel, anchor, delta, BORDER_DEFAULT);
}

int main(int argc, char** argv) {
    if (argc != 2) {
        cout << " Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_GRAYSCALE); // Lectura del archivo

    if (!image.data) // Chequea que sea un dato valido
    {
        cout << "no se puede abrir o encontrar la imagen" << endl;
        return -1;
    }

    cout << "el tipo de la imagen es:" << image.type() << "\n";
    Mat Resultado, histograma, blur;
    Mat Filtrada;
    Mat enfoque;
    Mat Casero;
    Mat median;
    Sharpen2(image, enfoque);
    filter(enfoque, Filtrada);
    Sharpen(Filtrada, Resultado);
    //filter(image, Filtrada);
    // Otsu's thresholding after Gaussian filtering
    GaussianBlur(image, blur, Size(5, 5), 0, 0);
    //ret3,th3 = cv2.threshold(blur,0,255,cv2.THRESH_BINARY+cv2.THRESH_OTSU)
    //Sharpen(image, Casero);
    //medianBlur(image, median, 5);
    //f_histograma(blur, histograma);
    threshold(blur);
    namedWindow("Imagen Original", CV_WINDOW_AUTOSIZE); // Crea una ventana
    imshow("Imagen Original", image); // Muestra nuestra imagen dentro de esta.
    namedWindow("Imagen filtro linea 1", CV_WINDOW_AUTOSIZE); // Crea una ventana con mejor enfoque
    imshow("Imagen filtro linea 1", Filtrada); // Muestra nuestra imagen enfocada dentro de esta.
    namedWindow("Imagen Realce Linea", CV_WINDOW_AUTOSIZE); // Crea una ventana de Realce Linea
    imshow("Imagen Realce Linea", Resultado); // Muestra nuestra imagen Realzada dentro de esta.
    namedWindow("Imagen filtro gausiano", CV_WINDOW_AUTOSIZE); // Crea una ventana de Realce Linea
    imshow("Imagen filtro gausiano", blur); // Muestra nuestra imagen Realzada dentro de esta.
    //namedWindow("Imagen filtro Casero", CV_WINDOW_AUTOSIZE); // Crea una ventana de Realce Linea
    //imshow("Imagen filtro Casero", Casero);
    //namedWindow("Imagen median filter", CV_WINDOW_AUTOSIZE); // Crea una ventana de Realce Linea
    //imshow("Imagen median filter", median);
    waitKey(0); // Espera por una tecla
    return 0;


}


