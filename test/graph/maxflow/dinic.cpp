#include <lib/graph/graph.hpp>
#include <lib/graph/maxflow/dinic.hpp>

#include <cassert>

int main() {
  int V = 4;
  nimi::maxflow_graph<int> g(V);

  g.add_edge(0, 1, 2);
  g.add_edge(0, 2, 1);
  g.add_edge(1, 2, 1);
  g.add_edge(1, 3, 1);
  g.add_edge(2, 3, 2);

  assert(dinic(g, 0, V - 1) == 3);
}
