# OpenCL Demonstrationt
OpenCL Demonstrationt .

-----

# Install OpenCL

**required**: Ubuntu 16.04, nvidia GPU and nvidia driver installed

```
sudo apt-get install nvidia-prime nvidia-modprobe nvidia-opencl-dev
sudo ln -s /usr/lib/x86_64-linux-gnu/libOpenCL.so.1 /usr/local/lib/libOpenCL.so
```

Test: `g++ maon.cpp -lOpenCL`
