#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

double now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void do_something_with_packaged_task() {
  std::packaged_task<int()> task([] {
    std::this_thread::sleep_for(5s);
    return 1000;
  });

  std::cout << "发起异步操作:" << std::endl;

  /// 使用std::thread模拟异步接口
  std::thread([&] { task(); }).detach();

  auto future = task.get_future();

  if (future.wait_for(1s) == std::future_status::timeout) {
    throw std::runtime_error("等待异步结果超时");
  }

  auto result = future.get();
  std::cout << "异步操作结果为: " << result << std::endl;
}

int main(int, char**) {
  auto n = now();
  std::cout << "开始使用packaged_task" << std::endl;
  try {
    do_something_with_packaged_task();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "使用完packaged_task, 用时: " << now() - n << "s" << std::endl;

  return 0;
}
