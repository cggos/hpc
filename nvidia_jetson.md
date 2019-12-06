# Nvidia Jetson

-----

* 查看系统信息
  ```sh
  cat /etc/lsb-release # 查看系统版本
  uname -a # 查看系统内核
  ```

* 查询Jetson设备与开发环境版本的基础信息
  http://www.gpus.cn/gpus_list_page_techno_support_content?id=39  

* 在jetson设备上使用以下命令可以查看系统的l4t的版本号
  ```sh
  head -n 1 /etc/nv_tegra_release
  ```

* 添加环境变量
  ```sh
  export PATH=/usr/local/cuda-8.0/bin:$PATH
  export LD_LIBRARY_PATH=/usr/local/cuda-8.0/lib64:$LD_LIBRARY_PATH
  ```

* 查看 cuda 版本
  ```sh
  cat /usr/local/cuda/version.txt
  ```
  or
  ```sh
  nvcc -V
  ```

* 查看 cudnn 版本
  ```sh
  cat /usr/local/cuda/include/cudnn.h | grep CUDNN_MAJOR -A 2
  cat /usr/include/cudnn.h | grep CUDNN_MAJOR -A 2
  ```

* 检测是否能查询显卡信息
  ```sh
  cd /usr/local/cuda-10.0/samples/1_Utilities/deviceQuery
  sudo make && ./deviceQuery
  ```

## 压力测试

https://www.tecmint.com/linux-cpu-load-stress-test-with-stress-ng-tool/

```sh
cat /sys/class/thermal/thermal_zone0/temp
```
