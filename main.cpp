#include <opencv2/opencv.hpp>

using namespace cv;


/* 
    g++ -o main main.cpp -std=c++11 $(pkg-config --cflags --libs opencv4)
*/

int main(int argc, char** argv)
{
    int camera = 0;
    VideoCapture cap;
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

        imshow("CHOMSKY", img_blur);
        imshow("This is you, smile!", frame);
        if (waitKey(1) == 27) break;
    }
    cap.release();
    return 0;
}
