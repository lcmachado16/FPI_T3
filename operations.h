#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;


using std::cout;
using std::endl;

void imprime();

//void contrast_and_brightness(cv::Mat& image,double alpha = 1.0,  int beta = 0);


/* Ajuste de brilho ::beta[0-100] */
void brightness(cv::Mat& image,int beta);
/* Contaste :: alpha[1.0-3.0]*/
void contrast(cv::Mat& image,double alpha);


void negative(cv::Mat& image);


cv::Mat vflip(const cv::Mat& src) ;


//  transpoe a matriz, e utiliza a funcao vflip, em seguida transpoe de volta
cv::Mat hflip(const cv::Mat& src) ;



/* ROTATIONS */
void rotate_90(cv::Mat& image);
