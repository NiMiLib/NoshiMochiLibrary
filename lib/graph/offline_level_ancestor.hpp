#ifndef NIMI_GRAPH_OFFLINELEVELANCESTOR
#define NIMI_GRAPH_OFFLINELEVELANCESTOR

#include <lib/graph/graph.hpp>
#include <cstddef>
#include <utility>
#include <vector>

namespace nimi {

template <class T>
std::vector<std::size_t> offline_level_ancestor(
    const directed_graph<T> &tree, const std::size_t root,
    const std::vector<std::pair<std::size_t, std::size_t>> &query) {
  class node_type {
  public:
    std::size_t v;
    bool s;
    constexpr node_type(const std::size_t v, const bool s) noexcept
        : v(v), s(s) {}
  };
  const std::size_t n = tree.size();
  const std::size_t q = query.size();
  std::vector<std::size_t> ans(q);
  std::vector<std::vector<std::size_t>> vtoq(n);
  for (std::size_t i = static_cast<std::size_t>(0); i != q; ++i) {
    vtoq[query[i].first].push_back(i);
  }
  std::vector<std::size_t> path;
  path.reserve(n);
  std::vector<node_type> stack;
  stack.reserve(n);
  stack.emplace_back(root, true);
  while (!stack.empty()) {
    if (stack.back().s) {
      stack.back().s = false;
      const std::size_t v = stack.back().v;
      path.push_back(v);
      for (const std::size_t i : vtoq[v]) {
        ans[i] = path[query[i].second];
      }
      for (const edge<T> &e : tree[v]) {
        stack.emplace_back(e.to, true);
      }
    } else {
      stack.pop_back();
      path.pop_back();
    }
  }
  return std::move(ans);
}

} // namespace nimi

#endif
