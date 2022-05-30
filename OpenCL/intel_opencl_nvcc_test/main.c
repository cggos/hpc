#include <stdlib.h>
#include <stdio.h>

#include <CL/cl.h>

int main(int argc, char** argv) {
  // Query OpenCL platforms, to be sure Intel OpenCL library is poked.
  cl_uint num_platforms;
  clGetPlatformIDs(0, NULL, &num_platforms);
  printf("Num platforms: %d\n", num_platforms);
  // Invoke NVCC. It will fail due to libigdrcl.so calling close on stdin.
  system("nvcc -arch=sm_61 --cubin kernel.cu -o kernel.cubin -m64 --ptxas-options=\"-v\"");
  return EXIT_SUCCESS;
}
