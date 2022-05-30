#include <iostream>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/ocl.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char** argv) {
  ocl::setUseOpenCL(true);

  namedWindow("disp", 1);

  Mat left, right, disp;
  UMat uleft, uright, udisp;

  left = cv::imread("/home/cg/Downloads/Cloth3/disp1.png", IMREAD_GRAYSCALE);
  right = cv::imread("/home/cg/Downloads/Cloth3/disp5.png", IMREAD_GRAYSCALE);

  left.copyTo(uleft);
  right.copyTo(uright);

  Ptr<StereoBM> bm = StereoBM::create(0, 21);
  bm->setPreFilterType(bm->PREFILTER_XSOBEL);
  bm->setTextureThreshold(0);

  bm->compute(left, right, disp);
  bm->compute(uleft, uright, udisp);

  disp.convertTo(disp, CV_8UC1, 255, 0);

  imshow("disp", disp);

  cv::waitKey();

  return 0;
}
