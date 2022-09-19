all:
	gcc -o intel_opencl_test main.c -lOpenCL
	gcc -shared -fPIC -o myclose.so close_preload.c

clean:
	rm -f intel_opencl_test myclose.so kernel.cubin
