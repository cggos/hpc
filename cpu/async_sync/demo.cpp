#include <condition_variable>
#include <future>
#include <iostream>
#include <string>
#include <thread>

namespace std_srvs {

struct SetIntegerRequest {
  int64_t data;
};

struct SetIntegerResponse {
  bool success;
  std::string message;
};

struct SetInteger {
  using Request = SetIntegerRequest;
  using Response = SetIntegerResponse;

  Request request;
  Response response;
};

}  // namespace std_srvs

template <typename MREQ, typename MRES>
struct Wrapper {
  using Request = MREQ;
  using Response = MRES;

  Wrapper(const Request& req) : m_request(req), m_response() {}

  const Request& request() const { return m_request; }

  const Response& response() const { return m_response; }

  Response& response() { return m_response; }

  void wait() {
    std::unique_lock<std::mutex> lock(m_reponse_lock);
    m_response_ready.wait(lock);
  }

  template <typename Rep, typename Period>
  std::cv_status wait_for(const std::chrono::duration<Rep, Period>& duration) {
    std::unique_lock<std::mutex> lock(m_reponse_lock);
    return m_response_ready.wait_for(lock, duration);
  }

  template <typename Clock, typename Duration>
  std::cv_status wait_until(const std::chrono::time_point<Clock, Duration>& time_point) {
    std::unique_lock<std::mutex> lock(m_reponse_lock);
    return m_response_ready.wait_until(lock, time_point);
  }

  void accept() {
    std::unique_lock<std::mutex> lock(m_reponse_lock);
    m_response_ready.notify_all();
  }

 private:
  Request m_request;
  Response m_response;

  std::mutex m_reponse_lock;
  std::condition_variable m_response_ready;
};

template <typename MREQ, typename MRES>
struct PromiseWrapper {
  using Request = MREQ;
  using Response = MRES;

  PromiseWrapper(const Request& req) : m_request(req) {}

  std::future<Response> get_future() { return m_response.get_future(); }

  const Request& request() const { return m_request; }

  void set_response(Response response) { m_response.set_value(std::move(response)); }

 private:
  Request m_request;
  std::promise<Response> m_response;
};

bool handle(const std_srvs::SetInteger::Request& request, std_srvs::SetInteger::Response& response) {
  auto wrapper = std::make_shared<Wrapper<std_srvs::SetInteger::Request, std_srvs::SetInteger::Response>>(request);

  /// 这里发起异步任务
  std::thread([=] {
    /// 模拟长时间，可以尝试将此处的时间和超时等待时间的长短交换看看结果
    std::this_thread::sleep_for(std::chrono::seconds(5));

    wrapper->response().success = true;
    wrapper->response().message = "success" + std::to_string(wrapper->request().data);

    wrapper->accept();  /// 接受任务结果
  }).detach();

  /// 这里等待异步任务的结果
  if (wrapper->wait_for(std::chrono::seconds(1)) == std::cv_status::no_timeout) {
    response = wrapper->response();
  } else {
    response.success = false;
    response.message = "timeout";
  }

  return true;
}

bool promise_handle(const std_srvs::SetInteger::Request& request, std_srvs::SetInteger::Response& response) {
  auto wrapper =
      std::make_shared<PromiseWrapper<std_srvs::SetInteger::Request, std_srvs::SetInteger::Response>>(request);
  /// 这里发起异步任务
  std::thread([=] {
    /// 模拟长时间，可以尝试将此处的时间和超时等待时间的长短交换看看结果
    std::this_thread::sleep_for(std::chrono::seconds(5));

    std_srvs::SetInteger::Response r;
    r.success = true;
    r.message = "success" + std::to_string(wrapper->request().data);

    wrapper->set_response(std::move(r));  /// 接受任务结果
  }).detach();

  auto future = wrapper->get_future();
  if (future.wait_for(std::chrono::seconds(1)) == std::future_status::timeout) {
    response.success = false;
    response.message = "promise timeout";
  } else {
    response = future.get();
  }

  return true;
}

void handle_test() {
  std_srvs::SetInteger srv;

  std::cout << "start: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
  handle(srv.request, srv.response);
  std::cout << "end  : " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;

  if (srv.response.success) {
    std::cout << srv.response.message << std::endl;
  } else {
    std::cerr << srv.response.message << std::endl;
  }
}

void promise_handle_test() {
  std_srvs::SetInteger srv;

  std::cout << "start: " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;
  promise_handle(srv.request, srv.response);
  std::cout << "end  : " << std::chrono::system_clock::now().time_since_epoch().count() << std::endl;

  if (srv.response.success) {
    std::cout << srv.response.message << std::endl;
  } else {
    std::cerr << srv.response.message << std::endl;
  }
}

int main(int, char**) {
  handle_test();
  promise_handle_test();

  return 0;
}
