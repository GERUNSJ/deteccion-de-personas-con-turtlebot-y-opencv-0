/*
 * histograma.hpp
 *
 *  Created on: 10/04/2014
 *      Author: pablo
 */


#ifndef HISTOGRAMA_HPP_
#define HISTOGRAMA_HPP_

using namespace cv;
using namespace std;

void f_histograma(const Mat& img)
{
    // Initialize parameters
    int histSize = 256;    // bin size
    float range[] = { 0, 65535 };
    const float *ranges[] = { range };

    // Calculate histogram
    Mat hist;
    calcHist( &img, 1, 0, Mat(), hist, 1, &histSize, ranges, true, false );
    //calcHist( &bgr_planes[0], 1, 0, Mat(), b_hist, 1, &histSize, &histRange, uniform, accumulate );

    cout << "zsdsdfgsrfghdfh" << std::endl;

    cout << "\nantes del log" << std::endl;
    for( int h = 0; h < histSize; h++ )
         {
            float binVal = hist.at<float>(h);
            cout<<" "<<binVal;
         }



    for(int i=0;i<hist.rows;i++)
    {
    	hist.at<float>(i) = log(hist.at<float>(i));
    	if(hist.at<float>(i)<0)hist.at<float>(i)=0;	//satura
    }

    // Show the calculated histogram in command window
    double total;
    total = img.rows * img.cols;

    cout << "\ndespues del log" << std::endl;

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




#endif /* HISTOGRAMA_HPP_ */
