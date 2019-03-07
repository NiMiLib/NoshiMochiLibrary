#ifndef NIMI_GRAPH_SP_DIJKSTRA
#define NIMI_GRAPH_SP_DIJKSTRA

#include <lib/graph/graph.hpp>
#include <limits>
#include <queue>
#include <vector>

namespace nimi {
  template<class T>
  std::vector<T> spfa(const nimi::directed_graph<T>& g, std::size_t s) {
    const T INF = std::numeric_limits<T>::max();
    const T ZERO = T();
    const std::size_t n = g.size();

    std::vector<T> dist(n, INF);
    std::vector<bool> inc(n, false);
    std::vector<std::size_t> cnt(n, 0);
    std::queue<int> que;
    dist[s] = ZERO;
    que.push(s);
    inc[s] = true;
    cnt[s]++;
    while(!que.empty()) {
      int v = que.front();
      que.pop();
      inc[v] = false;
      for(const auto& e: g[v]) {
        if(dist[v] + e.val < dist[e.to]) {
          dist[e.to] = dist[v] + e.val;
          if(!inc[e.to]) {
            que.push(e.to);
            inc[e.to] = true;
            cnt[e.to]++;
            if(cnt[e.to] >= n) return std::vector<T>();
          }
        }
      }
    }
    return std::move(dist);
  }
}
#endif
