#ifndef NIMI_GRAPH_SP_DIJKSTRA
#define NIMI_GRAPH_SP_DIJKSTRA

#include <lib/graph/graph.hpp>
#include <limits>
#include <queue>
#include <vector>

namespace nimi {
  template<class T>
  std::vector<T> dijkstra(const nimi::graph<T>& g, std::size_t s) {
    const T INF = std::numeric_limits<T>::max();
    const T ZERO = T();
    const std::size_t n = g.size();

    struct node {
      T dist;
      std::size_t vertex;
      node(T d, std::size_t v): dist(d), vertex(v) {  }
      bool operator<(const node& n) const {
        return n.dist < dist;
      }
    };

    std::vector<T> dist(n, INF);
    std::priority_queue<node> que;
  
    dist[s] = ZERO;
    que.emplace(dist[s], s);
  
    while(!que.empty()) {
      node p = que.top();
      T d = p.dist;
      std::size_t v = p.vertex;
      que.pop();
      if(dist[v] < d) continue;
      for(const auto& e: g[v]) {
        if(dist[v] + e.val < dist[e.to]) {
          dist[e.to] = dist[v] + e.val;
          que.emplace(dist[e.to], e.to);
        }
      }
    }
    return std::move(dist);
  }
}
#endif
