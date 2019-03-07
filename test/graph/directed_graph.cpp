#include <lib/graph/graph.hpp>
#include <iostream>
#include <cassert>

int main() {
    nimi::directed_graph<int> ng(5);

    ng.add_edge(nimi::edge<int>(0, 1, 5));

    assert(ng[0][0].val == 5);
}