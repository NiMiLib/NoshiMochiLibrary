#include <lib/data_structure/sequence/queue_aggregation>
#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <random>
#include <vector>

using u64 = std::uint_fast64_t;
using mat = std::array<std::array<u64, 2>, 2>;

int main() {
  const std::size_t n{10000};
  const std::size_t l{1000};

  const auto prod = [](const mat &l, const mat &r) {
    mat ret;
    for (std::size_t i{0}; i != 2; ++i) {
      for (std::size_t j{0}; j != 2; ++j) {
        ret[i][j] = 0;
        for (std::size_t k{0}; k != 2; ++k) {
          ret[i][j] += l[i][k] * r[k][j];
        }
      }
    }
    return ret;
  };

  std::default_random_engine engine{91};
  std::uniform_int_distribution<u64> val_dist{};
  nimi::queue_aggregation<mat, decltype(prod)> que{prod};
  std::vector<mat> bf{};
  for (std::size_t loop{0}; loop != n; ++loop) {
    if (!bf.empty() &&
        std::bernoulli_distribution{
            static_cast<double>(std::min(bf.size(), l)) / l}(engine)) {
      que.pop();
      bf.erase(bf.begin());
    } else {
      mat v;
      for (std::size_t i{0}; i != 2; ++i) {
        for (std::size_t j{0}; j != 2; ++j) {
          v[i][j] = val_dist(engine);
        }
      }
      que.push(v);
      bf.push_back(v);
    }

    mat acc;
    acc[0][0] = 1;
    acc[0][1] = 0;
    acc[1][0] = 0;
    acc[1][1] = 1;
    for (const mat &m : bf) {
      acc = prod(acc, m);
    }
    assert(que.empty() == bf.empty());
    assert(que.size() == bf.size());
    assert(que.fold_all() == acc);
  }
}
