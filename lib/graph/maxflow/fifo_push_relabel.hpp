#ifndef NIMI_GRAPH_MAXFLOW_FIFOPR
#define NIMI_GRAPH_MAXFLOW_FIFOPR

#include <lib/graph/graph.hpp>
#include <queue>
#include <vector>

namespace nimi {
  template<class C>
  C fifo_push_relabel(nimi::maxflow_graph<C>& g, std::size_t s, std::size_t t) {
    std::queue<int> que;
    std::size_t n = g.size();
    std::vector<C> ex(n);
    std::vector<int> d(n, 1);
    d[s] = n;
    d[t] = 0;
    C ZERO = C();

    for(auto& e: g[s]) {
      if(e.to != t && e.to != s && ex[e.to] == ZERO && e.cap > ZERO) {
        que.push(e.to);
      }
      ex[e.to] += e.cap;
      g[e.to][e.rev].cap = e.cap;
      e.cap = ZERO;
    }

    while(!que.empty()) {
      int v = que.front();
      que.pop();
      while(ex[v] > ZERO) {
        bool admissible = false;
        for(auto& e: g[v]) {
          if(d[v] == d[e.to] + 1 && e.cap > ZERO) {
            admissible = true;
            C delta = std::min(ex[v], e.cap);
            if(e.to != t && e.to != s && ex[e.to] == ZERO && delta > ZERO) {
              que.push(e.to);
            }
            ex[v] -= delta;
            ex[e.to] += delta;
            e.cap -= delta;
            g[e.to][e.rev].cap += delta;
          }
        }
        if(!admissible) {
          d[v] = n + 1;
          for(auto& e: g[v]) {
            if(e.cap > ZERO) {
              d[v] = std::min(d[v], d[e.to] + 1);
            }
          }
          if(v != s && v != t && ex[v] > ZERO && d[v] < n + 1) {
            que.push(v);
          }
          else {
            break;
          }
        }
      }
    }
    return ex[t];
  }
}

#endif
