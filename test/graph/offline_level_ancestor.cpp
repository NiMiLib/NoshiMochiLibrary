#include <lib/graph/graph.hpp>
#include <lib/graph/offline_level_ancestor.hpp>
#include <cassert>
#include <cstddef>
#include <random>
#include <vector>

namespace nimi {

void test() {
  const std::size_t n = 3000;
  const std::size_t q = 3000;
  std::default_random_engine engine(91);
  directed_graph<void> g(n);
  std::vector<std::size_t> rev(n), depth(n);
  for (std::size_t i = 1; i != n; ++i) {
    const std::size_t p =
        std::uniform_int_distribution<std::size_t>(0, i - 1)(engine);
    g.add_edge({int(p), int(i)});
    rev[i] = p;
    depth[i] = depth[p] + 1;
  }
  std::vector<std::pair<std::size_t, std::size_t>> query(q);
  for (auto &e : query) {
    e.first = std::uniform_int_distribution<std::size_t>(0, n - 1)(engine);
    e.second =
        std::uniform_int_distribution<std::size_t>(0, depth[e.first])(engine);
  }
  const std::vector<std::size_t> ans = offline_level_ancestor(g, 0, query);
  for (std::size_t i = 0; i != q; ++i) {
    std::size_t v = query[i].first;
    while (depth[v] > query[i].second) {
      v = rev[v];
    }
    assert(v == ans[i]);
  }
}

} // namespace nimi

int main() {
  nimi::test();
  return 0;
}
