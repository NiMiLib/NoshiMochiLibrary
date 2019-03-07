#ifndef NIMI_GRAPH
#define NIMI_GRAPH

#include <vector>

namespace nimi {
  struct base_edge {
    int from;
    int to;
    base_edge(int from, int to) : from(from), to(to) {  }
  };

  template<class T>
    struct edge : public base_edge {
      T val;
      edge(int from, int to, T v) : base_edge(from, to), val(v) {  }
    };

  template<>
    struct edge<void> : public base_edge {
      edge(int from, int to) : base_edge(from , to) {  }
    };

  template<class T>
  struct directed_graph : public std::vector<std::vector<edge<T>>> {
    directed_graph(std::size_t n): std::vector<std::vector<edge<T>>>(n) { }
    void add_edge(const edge<T>& e) { this->at(e.from).push_back(e); }
  };

  template<class T>
  struct undirected_graph : public std::vector<std::vector<edge<T>>> {
    undirected_graph(std::size_t n): std::vector<std::vector<edge<T>>>(n) { }
    void add_edge(const edge<T>& e) { this->at(e.from).push_back(e); this->at(e.to).push_back(edge<T>(e.to, e.from, e.val)); }
  };
}

#endif
