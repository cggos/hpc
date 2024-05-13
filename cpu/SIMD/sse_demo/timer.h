#include <ctime>
#include <iostream>
#include <string>

class Timer {
 public:
  Timer(const std::string &name) : name_(name), start_(std::clock()) {}

  ~Timer() {
    double elapsed = (double(std::clock() - start_) / double(CLOCKS_PER_SEC));
    std::cout << name_ << ": " << int(elapsed * 1000) << "ms" << std::endl;
  }

 private:
  std::string name_;
  std::clock_t start_;
};

#define TIMER(name) Timer timer__(name);