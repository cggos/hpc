#include <array>
#include <chrono>
#include <condition_variable>
#include <cstring>
#include <iostream>
#include <mutex>
#include <stdexcept>
#include <thread>

#include "hpc/cpu/shared_memory.h"

namespace {

constexpr char kSharedMemoryName[] = "/hpc_shared_memory_demo";
constexpr int kMessageCount = 5;

struct SharedState {
  bool ready;
  bool finished;
  int sequence;
  std::array<char, 256> message;
};

struct ThreadSync {
  std::mutex mutex;
  std::condition_variable cond;
};

void initialize_shared_state(SharedState* state) {
  state->ready = false;
  state->finished = false;
  state->sequence = 0;
  state->message.fill('\0');
}

void run_reader(SharedState* state, ThreadSync* sync) {
  while (true) {
    std::unique_lock<std::mutex> lock(sync->mutex);
    sync->cond.wait(lock, [state] { return state->ready || state->finished; });

    if (state->finished && !state->ready) {
      break;
    }

    std::cout << "[reader] sequence=" << state->sequence << ", message=" << state->message.data() << '\n';
    state->ready = false;
    lock.unlock();
    sync->cond.notify_one();
  }
}

void write_message(SharedState* state, ThreadSync* sync, int sequence) {
  std::unique_lock<std::mutex> lock(sync->mutex);
  sync->cond.wait(lock, [state] { return !state->ready; });

  state->sequence = sequence;
  const std::string text = "hello from writer #" + std::to_string(sequence);
  std::strncpy(state->message.data(), text.c_str(), state->message.size() - 1);
  state->message.back() = '\0';
  state->ready = true;

  lock.unlock();
  sync->cond.notify_one();
}

void finish_writer(SharedState* state, ThreadSync* sync) {
  std::unique_lock<std::mutex> lock(sync->mutex);
  sync->cond.wait(lock, [state] { return !state->ready; });

  state->finished = true;
  lock.unlock();
  sync->cond.notify_one();
}

}  // namespace

int main() {
  try {
    try {
      hpc::PosixSharedMemory::unlink(kSharedMemoryName);
    } catch (const std::exception&) {
    }

    hpc::PosixSharedMemory memory(kSharedMemoryName, sizeof(SharedState), hpc::PosixSharedMemory::OpenMode::Create);
    auto* state = memory.as<SharedState>();
    initialize_shared_state(state);

    ThreadSync sync;
    std::thread reader(run_reader, state, &sync);

    for (int i = 1; i <= kMessageCount; ++i) {
      write_message(state, &sync, i);
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    finish_writer(state, &sync);

    reader.join();
    hpc::PosixSharedMemory::unlink(kSharedMemoryName);

    std::cout << "[writer] reader thread joined\n";
    return 0;
  } catch (const std::exception& e) {
    std::cerr << "shared_memory_demo error: " << e.what() << '\n';
    try {
      hpc::PosixSharedMemory::unlink(kSharedMemoryName);
    } catch (const std::exception&) {
    }
    return 1;
  }
}
