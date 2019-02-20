#ifndef NIMI_GRAPH
#define NIMI_GRAPH

#include <vector>

struct base_edge {
  int from;
  int to;
  base_edge(int from, int to) : from(from), to(to) {  }
};

template<class T> struct edge : public base_edge {
  T val;
  edge(int from, int to, T v) : base_edge(from, to), val(v) {  }
};

template<> struct edge<void> : public base_edge {
  edge(int from, int to) : base_edge(from , to) {  }
};

#endif
