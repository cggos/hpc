#include <iostream>
#include <opencv2/core/ocl.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/videoio/videoio.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  ocl::setUseOpenCL(true);

  Mat gpuFrame;
  UMat gpuBW;
  UMat gpuBlur;
  UMat gpuEdges;

  namedWindow("edges", 1);

  VideoCapture cap(0);  // open the default camera
  if (!cap.isOpened())  // check if we succeeded
    return -1;

  for (;;) {
    cap >> gpuFrame;  // get a new frame from camera
    cvtColor(gpuFrame, gpuBW, COLOR_BGR2GRAY);

    GaussianBlur(gpuBW, gpuBlur, Size(1, 1), 1.5, 1.5);
    Canny(gpuBlur, gpuEdges, 0, 30, 3);

    imshow("edges", gpuEdges);

    waitKey(20);
  }

  // the camera will be deinitialized automatically in VideoCapture destructor

  return 0;
}
