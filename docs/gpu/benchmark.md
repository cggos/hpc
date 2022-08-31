# GPU Benchmark

---

* For the Raspberry Pi GPU benchmark, use the [OpenGL 2.1 test](https://www.geeks3d.com/20160215/raspberry-pi-opengl-2-1-support-tested-with-geexlab-0-9-6-0/) that comes with GeeXLab

* [msalvaris/gpu_monitor](https://github.com/msalvaris/gpu_monitor): Monitor your GPUs whether they are on a single computer or in a cluster

* [Benchmark Your Graphics Card On Linux](https://linuxconfig.org/benchmark-your-graphics-card-on-linux)

```sh
watch -n 10 nvidia-smi       # 每隔10秒更新一下显卡

# on Android
watch -n 0.1 adb shell cat /sys/class/kgsl/kgsl-3d0/gpu_busy_percentage # 0.1s
```
