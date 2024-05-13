#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

int main(int, char**) {
  std::async(std::launch::async, [] {
    std::cout << "这里是异步操作" << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "异步操作结束" << std::endl;
  });

  std::cout << "这里是异步操作发起后的同步操作" << std::endl;

  return 0;
}
