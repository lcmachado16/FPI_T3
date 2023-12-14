#include <opencv2/opencv.hpp>

using namespace cv;


/* g++ -o main main.cpp -std=c++11 $(pkg-config --cflags --libs opencv4)   */

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
        imshow("This is you, smile!", frame);
        if (waitKey(1) == 27) break;
    }
    cap.release();
    return 0;
}
