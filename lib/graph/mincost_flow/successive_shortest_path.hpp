#ifndef NIMI_GRAPH_MCF_SSP
#define NIMI_GRAPH_MCF_SSP

#include <lib/graph/graph.hpp>
#include <vector>
#include <set>
#include <limits>


namespace nimi {
  template<class C>
    std::pair<bool, C> successive_shortest_path(nimi::mcf_graph<C>& g, std::size_t s, std::size_t t, C f) {
      std::size_t n = g.size();
      C ZERO = C();
      C INF = std::numeric_limits<C>::max();
      C ans = ZERO;
      while(f > 0) {
        std::vector<C> dist(n, INF);
        std::vector<std::size_t> pv(n, -1);
        std::vector<std::size_t> pe(n, -1);

        dist[s] = ZERO;

        for(std::size_t c = 0;c < n;c++) {
          for(std::size_t v = 0;v < n;v++) {
            if(dist[v] == INF) continue;
            for(std::size_t i = 0;i < g[v].size();i++) {
              const auto& e = g[v][i];
              std::size_t u = e.to;
              if(e.cap == ZERO) continue;
              if(dist[u] > dist[v] + e.cost) {
                dist[u] = dist[v] + e.cost;
                pv[u] = v;
                pe[u] = i;
              }
            }
          }
        }

        if(pv[t] == -1) break;
        C ff = f;
        for(std::size_t u = t;u != s;u = pv[u]) {
          ff = std::min(ff, g[pv[u]][pe[u]].cap);
        }
        for(std::size_t u = t;u != s;u = pv[u]) {
          ans += ff * g[pv[u]][pe[u]].cost;
          g[pv[u]][pe[u]].cap -= ff;
          g[u][g[pv[u]][pe[u]].rev].cap += ff;
        }
        f -= ff;
      }

      if(f != ZERO) return { false, ZERO };
      else return { true, ans };
    }
}
#endif
