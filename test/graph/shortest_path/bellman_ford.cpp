#include <lib/graph/graph.hpp>
#include <lib/graph/shortest_path/bellman_ford.hpp>
#include <cassert>
#include <limits>
#include <vector>

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
    auto dist = std::move(nimi::bellman_ford(g,1));
    assert(dist[0].second == 3);
    assert(dist[1].second == 0);
    assert(dist[2].second == 2);
    assert(dist[3].second == std::numeric_limits<int>::max());
    return 0;
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
    };
    for(const auto& e : es) {
        g[e.from].push_back(e);
    }
    auto dist = std::move(nimi::bellman_ford(g,1));
    assert(dist[0].second == 0);
    assert(dist[1].second == 2);
    assert(dist[2].second == -3);
    assert(dist[3].second == -1);
    return 0;
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
    auto dist = std::move(nimi::bellman_ford(g,1));
    bool res = false;
    for(auto const& d: dist) {
      if(!d.first) res = true;
    }
    assert(res);
    return 0;
  }
}
