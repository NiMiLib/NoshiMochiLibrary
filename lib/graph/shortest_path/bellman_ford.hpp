#ifndef NIMI_GRAPH_SP_BELLMANFORD
#define NIMI_GRAPH_SP_BELLMANFORD

#include <lib/graph/graph.hpp>
#include <limits>
#include <vector>

namespace nimi {
  template<class T>
  std::vector<std::pair<bool, T>> bellman_ford(const nimi::directed_graph<T>& g, std::size_t s) {
    const std::size_t n = g.size();
    const T INF = std::numeric_limits<T>::max();
    std::vector<T> dist(n, INF);
    dist[s] = T();
    for(int i = 0;i < n;i++) {
      for(std::size_t v = 0;v < n;v++) {
        if(dist[v] == INF) continue;
        for(const auto& e: g[v]) {
          if(dist[v] + e.val < dist[e.to]) {
            dist[e.to] = dist[v] + e.val;
          }
        }
      }
    }
    std::vector<std::pair<bool, T>> res(n);
    for(int v = 0;v < n;v++) {
      res[v] = { true, dist[v] };
    }

    for(int i = 0;i < n;i++) {
      for(std::size_t v = 0;v < n;v++) {
        if(dist[v] == INF) continue;
        for(const auto& e: g[v]) {
          if(!res[v].first || dist[v] + e.val < dist[e.to]) res[e.to].second = false;
        }
      }
    }

    return std::move(res);
  }
}
#endif
