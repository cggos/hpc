# Nvidia Linux Install

-----

[TOC]

## Nvidia Graphics Card

* Check your Nvidia graphics card
  ```sh
  lspci | grep -E "VGA|3D"
  ```
  or
  ```sh
  lspci | grep -i vga
  lspci  -v -s 01:00.0
  ```

* check which driver is being used for Nvidia card
  ```sh
  sudo lshw -c display
  ```
  or
  ```sh
  sudo lshw -c video
  ```

* query and select driver
  ```sh
  prime-select query
  sudo prime-select nvidia
  ```

## Install Nvidia Drivers

* [2 Ways to Install Nvidia Driver on Ubuntu 18.04 (GUI & Command Line)](https://www.linuxbabe.com/ubuntu/install-nvidia-driver-ubuntu-18-04)

### disable and check nouveau  

* disable nouveau  
  ```sh
  sudo vim /etc/modprobe.d/blacklist.conf
  ```
  and add below in it
  ```sh
  blacklist nouveau
  options nouveau modeset=0
  ```
* update
  ```sh
  sudo update-initramfs -u
  ```
* reboot and check nouveau
  ```sh
  lsmod | grep nouveau
  ```

### download nvidia drivers

* https://www.geforce.com/drivers

### enter tty and turn off gui

* enter tty1
  ```sh
  ctrl+alt+f1
  ```
* turn off gui
  ```sh
  sudo service lightdm stop
  ```

### install nvidia drivers

```sh
sudo ./NVIDIA-Linux-x86_64-396.18.run -no-x-check -no-nouveau-check -no-opengl-files
```

### check status and settings

* check your installation status
  ```sh
  lsmod | grep nvidia
  ```
  or
  ```sh
  nvidia-smi
  ```

* settings
  ```sh
  nvidia-settings
  ```

### uninstall nvidia drivers

* uninstall nvidia drivers
  ```sh
  sudo apt-get purge nvidia-*
  ```
  or
  ```sh
  sudo /usr/bin/nvidia-uninstall
  ```


## Install CUDA

* https://developer.nvidia.com/cuda-toolkit

### download cuda

* cuda 9.0:
  https://developer.nvidia.com/cuda-90-download-archive?target_os=Linux&target_arch=x86_64&target_distro=Ubuntu&target_version=1604&target_type=runfilelocal

### install cuda

* install
  ```sh
  sudo sh cuda_9.0.176_384.81_linux.run
  ```

### add environment variables

* in .bashrc
  ```sh
  export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/cuda-9.0/lib64
  export PATH=$PATH:/usr/local/cuda-9.0/bin
  export CUDA_HOME=$CUDA_HOME:/usr/local/cuda-9.0
  ```

### check install status

* check
  ```sh
  nvcc --version
  ```

## Install NVIDIA-Docker

* [用nvidia-docker跑深度学习模型](https://blog.csdn.net/weixin_42749767/article/details/82934294)
