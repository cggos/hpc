#include <array>
#include <iostream>
#include <memory>
#include <new>
#include <vector>

#include "hpc/cpu/memory_pool.h"

struct Particle {
  int id{};
  float x{};
  float y{};
  float z{};
  std::array<float, 16> features{};

  Particle(int particle_id, float value) : id(particle_id), x(value), y(value * 2.0f), z(value * 3.0f) {
    features.fill(value);
  }

  float energy() const { return x * x + y * y + z * z; }
};

int main() {
  hpc::ObjectPool<Particle> pool(8);

  std::cout << "capacity=" << pool.capacity() << ", available=" << pool.available() << '\n';

  {
    std::vector<std::unique_ptr<Particle, hpc::ObjectPool<Particle>::Deleter>> particles;
    particles.reserve(6);

    for (int i = 0; i < 6; ++i) {
      particles.push_back(pool.make_unique(i, static_cast<float>(i + 1)));
    }

    std::cout << "after create: used=" << pool.used() << ", available=" << pool.available() << '\n';
    for (const auto& particle : particles) {
      std::cout << "particle " << particle->id << " energy=" << particle->energy() << '\n';
    }
  }

  std::cout << "after scope: used=" << pool.used() << ", available=" << pool.available() << '\n';

  try {
    std::vector<std::unique_ptr<Particle, hpc::ObjectPool<Particle>::Deleter>> particles;
    for (int i = 0; i < 9; ++i) {
      particles.push_back(pool.make_unique(i, 1.0f));
    }
  } catch (const std::bad_alloc&) {
    std::cout << "pool exhausted: fixed capacity reached\n";
  }

  std::cout << "final: used=" << pool.used() << ", available=" << pool.available() << '\n';
  return 0;
}
