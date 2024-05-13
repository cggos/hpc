#include <future>
#include <iostream>

using namespace std::literals::chrono_literals;

double now() {
  return std::chrono::duration_cast<std::chrono::duration<double>>(std::chrono::system_clock::now().time_since_epoch())
      .count();
}

void do_something_with_promise() {
  std::promise<int> promise;

  std::cout << "发起异步操作:" << std::endl;

  /// 暂时用std::thread模拟下异步接口
  std::thread([&] {
    std::this_thread::sleep_for(5s);
    promise.set_value(1000);
  }).detach();

  auto future = promise.get_future();

  if (future.wait_for(1s) == std::future_status::timeout) {
    throw std::runtime_error("等待异步结果超时");
    // std::cout << "等待异步结果超时" << std::endl;
    // return;
  }

  auto result = future.get();
  std::cout << "异步操作结果为: " << result << std::endl;
}

int main(int, char**) {
  auto n = now();
  std::cout << "开始使用promise" << std::endl;
  try {
    do_something_with_promise();
  } catch (const std::exception& e) {
    std::cout << e.what() << std::endl;
  }
  std::cout << "使用完promise, 用时: " << now() - n << "s" << std::endl;

  return 0;
}
