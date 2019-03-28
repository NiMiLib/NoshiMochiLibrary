#include <algorithm>
#include <cassert>
#include <cstddef>
#include <lib/data_structure/heap/pairing_heap.hpp>
#include <random>
#include <vector>

int main() {
  const std::size_t n = 100;
  std::mt19937_64 engine(91);
  nimi::pairing_heap<std::uint_fast64_t> heap;
  std::vector<std::uint_fast64_t> vec;

  for (std::size_t i = 0; i != n; ++i) {
    heap.push(engine());
  }

  while (!heap.empty()) {
    vec.push_back(heap.top());
    heap.pop();
  }

  assert(vec.size() == n);
  assert(std::is_sorted(vec.crbegin(), vec.crend()));

  return 0;
}
