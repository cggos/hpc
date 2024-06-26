#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex g_display_mutex;

void foo() {
  std::thread::id this_id = std::this_thread::get_id();

  g_display_mutex.lock();
  std::cout << "thread " << this_id << " sleeping...\n";
  g_display_mutex.unlock();

  std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() {
  unsigned int n = std::thread::hardware_concurrency();
  std::cout << n << " concurrent threads are supported.\n";

  std::thread t1(foo);
  std::thread t2(foo);

  t1.join();
  t2.join();
}
