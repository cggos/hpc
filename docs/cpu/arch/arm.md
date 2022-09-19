# ARM

---

## Android Performance

```sh
adb shell "echo performance > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_setspeed"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu0/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_setspeed"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_max_freq"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu1/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu1/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu1/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_setspeed"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_max_freq"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu2/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu2/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_setspeed"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_max_freq"
adb shell "echo 1766400 > /sys/devices/system/cpu/cpu3/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu3/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu3/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_setspeed"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_max_freq"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu4/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu4/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu4/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu5/cpufreq/scaling_governor"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu5/cpufreq/scaling_setspeed"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu5/cpufreq/scaling_max_freq"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu5/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu5/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu5/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu6/cpufreq/scaling_governor"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu6/cpufreq/scaling_setspeed"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu6/cpufreq/scaling_max_freq"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu6/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu6/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu6/cpufreq/scaling_governor
adb shell "echo performance > /sys/devices/system/cpu/cpu7/cpufreq/scaling_governor"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu7/cpufreq/scaling_setspeed"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu7/cpufreq/scaling_max_freq"
adb shell "echo 2649600 > /sys/devices/system/cpu/cpu7/cpufreq/scaling_min_freq"
adb shell cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_cur_freq
adb shell cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_max_freq
adb shell cat /sys/devices/system/cpu/cpu7/cpufreq/cpuinfo_min_freq
adb shell cat /sys/devices/system/cpu/cpu7/cpufreq/scaling_governor
```
