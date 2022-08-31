# CPU Info

---

## Overview

8 commands to check cpu information on Linux:  

* **/proc/cpuinfo**: The `/proc/cpuinfo` file contains details about individual cpu cores.

* **lscpu**: simply print the cpu hardware details in a user-friendly format

* **cpuid**: fetches `CPUID` information about Intel and AMD x86 processors

* **nproc**: just prints out the number of processing units available, note that the number of processing units might not always be the same as number of cores

* **dmidecode**: displays some information about the cpu, which includes the socket type, vendor name and various flags

* **hardinfo**: would produce a large report about many hardware parts, by reading files from the `/proc` directory

* **lshw -class processor**: lshw by default shows information about various hardware parts, and the `-class` option can be used to pickup information about a specific hardware part

* **inxi**: a script that uses other programs to generate a well structured easy to read report about various hardware components on the system

## ARM CPU features

* [Runtime detection of CPU features on an ARMv8-A CPU](https://community.arm.com/android-community/b/android/posts/runtime-detection-of-cpu-features-on-an-armv8-a-cpu)
