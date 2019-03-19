#include <lib/graph/graph.hpp>
#include <lib/graph/mincost_flow/successive_shortest_path.hpp>

#include <cassert>

int main() {
  int V = 4;

  nimi::mcf_graph<int> g(V);

  g.add_edge(0, 1, 2, 1);
  g.add_edge(0, 2, 1, 2);
  g.add_edge(1, 2, 1, 1);
  g.add_edge(1, 3, 1, 3);
  g.add_edge(2, 3, 2, 1);

  assert(nimi::successive_shortest_path(g, 0, 3, 2).second == 6);
}
