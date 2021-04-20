/************************************************
 * 该例程讲解了进程、线程绑定到固定的cpu核心上运行
 * 来提高程序运行效率
************************************************/
#include <unistd.h>
#ifndef __USE_GNU
#define __USE_GNU  // 为了使用SET_SET()等宏定义，但unistd.h里面好像已经定义了
#endif
#include <pthread.h>
#include <sched.h>
#include <stdio.h>
#include <sys/syscall.h>

#include <iostream>
#include <thread>
#include <vector>

unsigned int systemCPUNum() {
    return sysconf(_SC_NPROCESSORS_CONF);  // _SC_NPROCESSORS_CONF的值为CPU个数，基于0开始编号
}

void setCurrentThreadAffinityMask(int mask, pid_t pid) {
    int err;
    int syscallres = syscall(__NR_sched_setaffinity, pid, sizeof(mask), &mask);
    if (syscallres) {
        // err = errno;
        // LOGE("Error in the syscall setaffinity: mask=%d=0x%x err=%d=0x%x", mask, mask, err, err);
    }
}

inline bool set_thread_affinity(pthread_t th, const std::vector<unsigned int>& cpu_ids) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    for (const auto& id : cpu_ids) CPU_SET(id, &cpuset);
    int ret = pthread_setaffinity_np(th, sizeof(cpuset), &cpuset);
    return ret >= 0;
    // setCurrentThreadAffinityMask(th, (int)cpuset.__bits);
    // sched_setaffinity(th, sizeof(cpuset), &cpuset);
    // return true;
}

inline bool get_thread_affinity(pthread_t th, std::vector<unsigned int>& cpu_ids) {
    cpu_set_t cpuset;
    CPU_ZERO(&cpuset);
    int ret = pthread_getaffinity_np(th, sizeof(cpuset), &cpuset);
    // int ret = sched_getaffinity(th, sizeof(cpuset), &cpuset);
    if (ret < 0) return false;

    unsigned int cpu_num = sysconf(_SC_NPROCESSORS_CONF);  // std::thread::hardware_concurrency(); // sysconf(_SC_NPROCESSORS_CONF); // _SC_NPROCESSORS_CONF的值为CPU个数，基于0开始编号
    cpu_ids.clear();
    for (unsigned int i = 0; i < cpu_num; ++i) {
        if (CPU_ISSET(i, &cpuset)) cpu_ids.push_back(i);
    }

    return true;
}

bool currentProcessAffinity(std::vector<unsigned int>& runningCPUVector) {
    cpu_set_t cpuSet;

    CPU_ZERO(&cpuSet);

    // 得到指定进程ID绑定到哪个CPU
    int ret = sched_getaffinity(0, sizeof(cpuSet), &cpuSet);
    if (ret < 0) {
        return false;
    }

    unsigned int cpuNum = systemCPUNum();
    runningCPUVector.clear();
    for (unsigned int i = 0; i < cpuNum; ++i) {
        // 检查一个CPU号是否在一个集合中
        if (CPU_ISSET(i, &cpuSet)) {
            runningCPUVector.push_back(i);
        }
    }

    return true;
}

bool setCurrentProcessAffinity(const std::vector<unsigned int>& needBindCPUVector) {
    cpu_set_t cpuSet;

    CPU_ZERO(&cpuSet);

    for (auto& iter : needBindCPUVector) {
        CPU_SET(iter, &cpuSet);
    }

    // 将指定进程ID绑定到CPU, 0代表当前进程
    int ret = sched_setaffinity(0, sizeof(cpuSet),  &cpuSet);
    if (ret < 0) {
        return false;
    }

    return true;
}

int main() {
    printf("*****Process bind CPU sample*****\n");
    unsigned int cpuNum = systemCPUNum();
    printf("Current system has %u CPU(s)\n", cpuNum);

    std::vector<unsigned int> runningCPUVector;
    if (!currentProcessAffinity(runningCPUVector)) {
        printf("Get current process was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector) {
        printf("Current process is running at %u CPU\n", iter);
    }

    std::vector<unsigned int> needBindCPUVector{0, 2};
    if (!setCurrentProcessAffinity(needBindCPUVector)) {
        printf("Current process bind CPU failed\n");
        return 1;
    }

    printf("Current process bind CPU success\n");

    runningCPUVector.clear();
    if (!currentProcessAffinity(runningCPUVector)) {
        printf("Get current process was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector) {
        printf("Current process is running at %u CPU\n", iter);
    }

    printf("\n*****Thread bind CPU sample*****\n");
    runningCPUVector.clear();
    if (!get_thread_affinity(pthread_self(), runningCPUVector)) {
        printf("Get current thread was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector) {
        printf("Thread %lu is running at %u CPU\n", pthread_self(), iter);
    }

    needBindCPUVector.clear();
    needBindCPUVector.push_back(1);
    if (!set_thread_affinity(pthread_self(), needBindCPUVector)) {
        printf("Current thread bind CPU failed\n");
        return 1;
    }

    printf("Thread %lu bind CPU success\n", pthread_self());

    runningCPUVector.clear();
    if (!get_thread_affinity(pthread_self(), runningCPUVector)) {
        printf("Get current thread was bound witch CPU failed\n");
        return 1;
    }

    for (auto& iter : runningCPUVector) {
        printf("Thread %lu is running at %u CPU\n", pthread_self(), iter);
    }

    {
        std::thread thread1;
        std::vector<unsigned int> cpu_ids{0, 1, 2, 3, 4, 5};
        cpu_set_t cpuset;
        CPU_ZERO(&cpuset);
        for (const auto& id : cpu_ids) {
            CPU_ZERO(&cpuset);
            CPU_SET(id, &cpuset);
            int ret1 = syscall(__NR_sched_setaffinity, thread1.native_handle(), sizeof(cpuset.__bits), &cpuset.__bits);

            CPU_ZERO(&cpuset);
            // int ret2 = sched_getaffinity(thread_backend.native_handle(), sizeof(cpuset), &cpuset);
            int ret2 = syscall(__NR_sched_getaffinity, thread1.native_handle(), sizeof(cpuset.__bits), &cpuset.__bits);

            unsigned int cpu_num = sysconf(_SC_NPROCESSORS_CONF);
            cpu_ids.clear();
            for (unsigned int i = 0; i < cpu_num; ++i) {
                if (CPU_ISSET(i, &cpuset)) cpu_ids.push_back(i);
            }

            printf("[cggos cpu %d] thread_backend %s, ret1 %d, ret2 %d, cpu_ids %d size: ", id, __FUNCTION__, ret1, ret2, cpu_ids.size());
            for (int i = 0; i < cpu_ids.size(); i++) {
                std::cout << cpu_ids[i] << " ";
            }
            std::cout << std::endl;
        }
    }

    return 0;
}