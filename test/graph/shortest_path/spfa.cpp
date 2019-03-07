#include <lib/graph/graph.hpp>
#include <lib/graph/shortest_path/spfa.hpp>
#include <cassert>
#include <limits>
#include <vector>
#include <iostream>

int main() {
  {
    using E = nimi::edge<int>;
    nimi::directed_graph<int> g(4);
    std::vector<E> es = {
        E(0,0,1),
        E(0,2,4),
        E(2,0,1),
        E(1,2,2),
        E(3,1,1),
        E(3,2,5)
    };
    for(const auto& e : es) {
        g[e.from].push_back(e);
    }
    auto dist = std::move(nimi::spfa(g,1));
    assert(dist[0] == 3);
    assert(dist[1] == 0);
    assert(dist[2] == 2);
    assert(dist[3] == std::numeric_limits<int>::max());
  }
  {
    using E = nimi::edge<int>;
    nimi::directed_graph<int> g(4);
    std::vector<E> es = {
        E(0,1,2),
        E(0,2,3),
        E(1,2,-5),
        E(1,3,1),
        E(2,3,2),
        E(3,1,0)
    };
    for(const auto& e : es) {
        g[e.from].push_back(e);
    }
    auto dist = std::move(nimi::spfa(g,1));
    assert(dist.empty());
  }
    return 0;
}
