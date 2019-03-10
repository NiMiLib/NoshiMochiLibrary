#ifndef NIMI_GRAPH_MAXFLOW_DINIC
#define NIMI_GRAPH_MAXFLOW_DINIC

#include <lib/graph/graph.hpp>
#include <limits>
#include <queue>
#include <vector>
#include <functional>

namespace nimi {
  template<class C>
  C dinic(nimi::maxflow_graph<C>& g, std::size_t s, std::size_t t) {
    C inf = std::numeric_limits<C>::max();
    C ans = 0;
    std::size_t n = g.size();

    std::vector<int> level(n);
    std::vector<std::size_t> iter(n);

    std::function<void(void)> g_level = [&]() {
      level.assign(n, -1);
      std::queue<int> que;
      que.push(s);
      level[s] = 0;
      while(!que.empty()) {
        int v = que.front();
        que.pop();
        for(const auto& e: g[v]) {
          if(e.cap > 0 && level[e.to] == -1) {
            level[e.to] = level[e.from] + 1;
            que.push(e.to);
          }
        }
      }
    };

    std::function<C(int, C)> dinic_dfs = 
      [&](int v, C f) {
        if(v == t) return f;
        C now = f;

        for(std::size_t& i = iter[v];i < g[v].size();i++) {
          auto& e = g[v][i];
          if(e.cap > 0 && level[e.to] > level[e.from]) {
            C ff = dinic_dfs(e.to, std::min(now, e.cap));
            e.cap -= ff;
            g[e.to][e.rev].cap += ff;
            now -= ff;
          }
        }
        return f - now;
      };

    while(1) {
      g_level();
      if(level[t] < 0) break;
      C f;
      iter.assign(n, 0);
      while((f = dinic_dfs(s, inf)) > 0) {
        ans += f;
      }
    }

    return ans;
  }
} 

#endif
