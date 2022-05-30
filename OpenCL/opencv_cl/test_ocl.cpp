
#include <fstream>
#include <iostream>
#include <iterator>
#include <opencv2/core/ocl.hpp>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;

int main() {
  if (!cv::ocl::haveOpenCL())
    cout << "OpenCL is not avaiable..." << endl;
  else
    cout << "OpenCL is AVAILABLE! :) " << endl;  // this is the output

  //   cv::ocl::setUseOpenCL(true);

  cv::ocl::Context context = cv::ocl::Context::getDefault();

  cout << context.ndevices() << " GPU devices are detected." << endl;

  for (int i = 0; i < context.ndevices(); i++) {
    cv::ocl::Device device = context.device(i);
    cout << "name:              " << device.name() << endl;
    cout << "available:         " << device.available() << endl;
    cout << "imageSupport:      " << device.imageSupport() << endl;
    cout << "OpenCL_C_Version:  " << device.OpenCL_C_Version() << endl;
    cout << endl;
  }  // this works & i can see my video card name & opencl version

  cv::ocl::Device(context.device(0));
}
