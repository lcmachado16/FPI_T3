#include <opencv2/opencv.hpp>

#include "operations.h"

using namespace cv;
using namespace std;


/* 
    g++ -o main main.cpp -std=c++11 $(pkg-config --cflags --libs opencv4)
*/

int lowThreshold = 0;
const int max_lowThreshold = 100;
const double const_ratio = 3;

const char* window_name = "FPI UFRGS";
const char* kernel_trackbar = "Kernel_Size::";
const char* brightness_trackbar = "Brightness::";
const char* contrast_trackbar = "Contrast::";


int kernel_size = 3;

//![variables]
Mat src, src_gray;
Mat dst, detected_edges;

bool is_gray = false;
bool is_gaussian_blur = false;
bool is_hflip = false;
bool is_vflip = false;
bool is_canny = false;
bool is_rotated = false;
bool is_brilho = true;  // ATENCAO
bool is_sobel = false;
bool is_reduced = false;
bool is_negative = false;

static void on_trackbar( int, void* )
{
    cout << "CHomsky" << endl;
}



int main(int argc, char** argv)
{
    int camera = 0;
    VideoCapture cap(0);

    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(camera))
        return 0;

    // Cria trackbar para ajustar brilho
    int iSliderValue1 = 0;
    int iSliderValue2 = 50;



    cv::namedWindow(window_name);
    createTrackbar(kernel_trackbar, window_name, NULL, 32, 0);
    createTrackbar(brightness_trackbar, window_name, NULL, 300, 0);
    createTrackbar(contrast_trackbar, window_name, NULL, 300, 0);

    for(;;)
    {
        Mat frame;
        cap >> frame;
        if( frame.empty() ) break; // end of video stream
        

       



        Mat image;
        Mat img_gray;
        Mat img_blur; 
        Mat img_canny;
        Mat aux;
        cap.read(image);
        cvtColor(image,img_gray,COLOR_BGR2GRAY);


        //blur( img_gray, detected_edges, Size(3,3) );
        //Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*const_ratio, kernel_size );

       // imshow("CHOMSKY", detected_edges);


        // cv::Mat resized;
        // cv::resize(frame, resized, cv::Size(800, 600));
        // cv::imshow("resized",resized);


        // image.convertTo(new_image, -1, alpha, beta);



        Mat output_image = image; 
        

        //cv::rotate(image, output_image, cv::ROTATE_90_CLOCKWISE);

        if(is_rotated) {
            rotate_90(output_image);
        }

        if (is_gaussian_blur){
            GaussianBlur(output_image, output_image, Size(9,9),0,0);
        }
        output_image = is_gray ? img_gray : output_image ;
        output_image = is_hflip ? hflip(output_image) : output_image ;
        output_image = is_vflip ? vflip(output_image) : output_image ;
        if (is_negative) {
            negative(output_image);
        }
        
        if(is_canny){
            aux = output_image;
            Canny(aux,output_image, 50,150);
        }
          
        if(is_brilho){
            double contrast_value  = cv::getTrackbarPos(contrast_trackbar, window_name) + 100;
            contrast_value = contrast_value / 100 ;
            double brightness_value = cv::getTrackbarPos(brightness_trackbar, window_name);
           
            // Convertendo a imagem para outro tipo de dados com ganho e deslocamento automáticos
            output_image.convertTo(output_image, -1, contrast_value, brightness_value);
        }


        if(is_sobel){
            cv::Mat gradX, gradY, gradient;
                  // Aplica o operador Sobel nos eixos X e Y
            cv::Sobel(img_gray, gradX, CV_16S, 1, 0, 3);
            cv::Sobel(img_gray, gradY, CV_16S, 0, 1, 3);

            // Calcula o gradiente total usando a magnitude
            cv::convertScaleAbs(gradX, gradX);
            cv::convertScaleAbs(gradY, gradY);
            cv::addWeighted(gradX, 0.5, gradY, 0.5, 0, gradient);
            output_image = gradient;
        }

        if(is_reduced){
            int height = output_image.rows;
            int width = output_image.cols;
            int layers = output_image.channels();

            int new_h = static_cast<int>(height / 2);
            int new_w = static_cast<int>(width / 2);

            cv::Mat resized_frame;
            cv::resize(output_image, resized_frame, cv::Size(new_w, new_h));
            
            imshow(window_name, resized_frame);
        }else{
            
        imshow(window_name, output_image);

        }

        int pressed_key = cv::waitKey(1);
        if (pressed_key == 27) break;
        else if (pressed_key == 'g' || pressed_key == 'G') {
            cout << "G was pressed " << endl;
            is_gray = !is_gray;
        }
         else if (pressed_key == 'c' || pressed_key == 'C') {
            cout << "C was pressed " << endl;
            is_canny = !is_canny;
        }

        else if (pressed_key == 'h' || pressed_key == 'H') {
            cout << "H was pressed " << endl;
            is_hflip = !is_hflip;
        }
        else if (pressed_key == 'v' || pressed_key == 'V') {
            cout << "V was pressed " << endl;
            is_vflip = !is_vflip;
        }


        else if (pressed_key == 'b' || pressed_key == 'B') {
            cout << "B was pressed " << endl;
            is_gaussian_blur = !is_gaussian_blur;
        }

        else if (pressed_key == 'r' || pressed_key == 'R') {
            cout << "R was pressed " << endl;
            is_rotated = !is_rotated;
        }

        else if (pressed_key == 'a' || pressed_key == 'A') {
            cout << "A was pressed " << endl;
            is_brilho = !is_brilho;
        }

        else if (pressed_key == 's' || pressed_key == 'S') {
            cout << "S was pressed " << endl;
            is_sobel = !is_sobel;
        }
         else if (pressed_key == 'n' || pressed_key == 'N') {
            cout << "N was pressed " << endl;
            is_negative = !is_negative;
        }

        else if (pressed_key == 'd' || pressed_key == 'D') {
            cout << "D was pressed " << endl;
            is_reduced = !is_reduced;
        }


 
      

   
    }
    cap.release();
    return 0;
}


/* 
 * TO DO:
 * [ ] - Gaussian Blur 
 * [ ] - Canny 
 * [ ] - Sobel 
 * [ ] - convertTo
 * [ X ] - converter para tons de cinza 
 * [ ] - Redimensionamento de video 
 * [ ] - Rotacao de 90 graus 
 * [ ] - Espelhamento de vídeo (horizontal e vertical)
 *
*/