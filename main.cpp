#include <opencv2/opencv.hpp>

#include "operations.h"

using namespace cv;
using namespace std;


/* 
    g++ -o main main.cpp -std=c++11 $(pkg-config --cflags --libs opencv4)
*/

int lowThreshold = 0;
const int max_lowThreshold = 100;
const double ratio = 3;
const int kernel_size = 3;
const char* window_name = "Edge Map";

bool is_gray = false;
bool is_gaussian_blur = false;
bool is_hflip = false;
bool is_vflip = false;
bool is_canny = false;


int main(int argc, char** argv)
{
    int camera = 0;
    VideoCapture cap(0);

       // Define a largura e a altura desejadas
    int desired_width = 300;
    int desired_height = 300;

    // Define o tamanho do frame
    cap.set(cv::CAP_PROP_FRAME_WIDTH, desired_width);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, desired_height);
    // open the default camera, use something different from 0 otherwise;
    // Check VideoCapture documentation.
    if(!cap.open(camera))
        return 0;
    for(;;)
    {
        Mat frame;
        cap >> frame;
        if( frame.empty() ) break; // end of video stream

        Mat image;
        Mat img_gray;
        Mat img_blur; 
        cap.read(image);
        cvtColor(image,img_gray,COLOR_BGR2GRAY);
        GaussianBlur(image, img_blur, Size(9,9),3,0);

        //![variables]
        Mat src, src_gray;
        Mat dst, detected_edges;

        //blur( img_gray, detected_edges, Size(3,3) );
        //Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

       // imshow("CHOMSKY", detected_edges);


        // cv::Mat resized;
        // cv::resize(frame, resized, cv::Size(800, 600));
        // cv::imshow("resized",resized);

        Mat output_image = image; 
        

        //cv::rotate(image, output_image, cv::ROTATE_90_CLOCKWISE);

        if (is_gaussian_blur){
            GaussianBlur(output_image, output_image, Size(9,9),0,0);
        }
        if (is_gray){
            output_image = img_gray;
        }
        output_image = is_gray ? img_gray : output_image ;

        //hflip
        output_image = is_hflip ? hflip(output_image) : output_image ;
        output_image = is_vflip ? vflip(output_image) : output_image ;


        imshow("Original", is_gray ? output_image : output_image);

        int pressed_key = cv::waitKey(1);
        if (pressed_key == 27) break;
        else if (pressed_key == 'g' || pressed_key == 'G') {
            cout << "G was pressed " << endl;
            is_gray = !is_gray;
        }
         else if (pressed_key == 'c' || pressed_key == 'C') {
            cout << "G was pressed " << endl;
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