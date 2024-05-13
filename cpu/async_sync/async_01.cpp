#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

int main(int, char**) {
  auto future = std::async(std::launch::async, [] {
    std::cout << "这里是异步操作" << std::endl;
    std::this_thread::sleep_for(1s);
    std::cout << "异步操作结束" << std::endl;
    return 1000;
  });

  std::cout << "这里是异步操作发起后的同步操作" << std::endl;

  std::this_thread::sleep_for(500ms);
  auto result = future.get();

  std::cout << "异步操作结果为: " << result << std::endl;

  return 0;
}
