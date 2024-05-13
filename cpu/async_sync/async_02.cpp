#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

double now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void do_something_with_future() {
  auto future = std::async(std::launch::async, [] {
    std::cout << "这里是异步操作" << std::endl;
    std::this_thread::sleep_for(5s);
    std::cout << "异步操作结束" << std::endl;
    return 1000;
  });

  std::cout << "这里是异步操作发起后的同步操作" << std::endl;

  std::this_thread::sleep_for(500ms);
  if (future.wait_for(1s) == std::future_status::timeout) {
    std::cout << "等待异步结果超时" << std::endl;
    return;
  }

  auto result = future.get();

  std::cout << "异步操作结果为: " << result << std::endl;
}

int main(int, char**) {
  auto n = now();
  std::cout << "还没有使用future" << std::endl;
  do_something_with_future();
  std::cout << "使用完future, 用时" << now() - n << "s" << std::endl;

  return 0;
}
