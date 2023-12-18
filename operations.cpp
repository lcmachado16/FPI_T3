#include "operations.h"



void imprime(){
    cout << "Chomskyyyyy" << endl;
}


/* Ajuste de brilho :: beta[0-100] */
void brightness(cv::Mat& image,int beta){
    double alpha = 1.0; // Alpha :: contrast_adjustment 
    Mat new_image = Mat::zeros( image.size(), image.type() );
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    image = new_image;
}
/* Contaste :: alpha[1.0-3.0]*/
void contrast(cv::Mat& image,double alpha){
    int beta = 0; // beta :: brightness_adjustment 
    Mat new_image = Mat::zeros( image.size(), image.type() );
    for( int y = 0; y < image.rows; y++ ) {
        for( int x = 0; x < image.cols; x++ ) {
            for( int c = 0; c < image.channels(); c++ ) {
                new_image.at<Vec3b>(y,x)[c] =
                  saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
            }
        }
    }
    image = new_image;
}

// void contrast_and_brightness(cv::Mat& image,double alpha = 1.0,  int beta = 0){
//      //contrast
//     Mat new_image = Mat::zeros( image.size(), image.type() );
//     for( int y = 0; y < image.rows; y++ ) {
//         for( int x = 0; x < image.cols; x++ ) {
//             for( int c = 0; c < image.channels(); c++ ) {
//                 new_image.at<Vec3b>(y,x)[c] =
//                   saturate_cast<uchar>( alpha*image.at<Vec3b>(y,x)[c] + beta );
//             }
//         }
//     }
//     image = new_image;
// }

void negative(cv::Mat& image) {
    cv::Mat new_image = cv::Mat::zeros(image.size(), image.type());

    for (int y = 0; y < image.rows; y++) {
        for (int x = 0; x < image.cols; x++) {
            for (int c = 0; c < image.channels(); c++) {
                new_image.at<cv::Vec3b>(y, x)[c] = 255 - image.at<cv::Vec3b>(y, x)[c];
            }
        }
    }
    image = new_image;
    
}


cv::Mat vflip(const cv::Mat& src) {
    int columns = src.cols;
    int rows = src.rows;
    cv::Mat dst(rows, columns, src.type());

    for (int i = 0; i < rows; i++) {
        cv::Mat row = src.row(i);
        std::memcpy(dst.row(rows - i - 1).data, row.data, src.cols * src.elemSize());
    }

    return dst;
}

//  transpoe a matriz, e utiliza a funcao vflip, em seguida transpoe de volta
cv::Mat hflip(const cv::Mat& src) {
    cv::Mat img_aux = src.t();
    cv::Mat dst = vflip(img_aux).t();
    return dst;
}



void rotate_90(cv::Mat& image) {
    // Verificar se a imagem é colorida
    cv::Mat new_image = image.t();
    image = hflip(new_image);
    
}
