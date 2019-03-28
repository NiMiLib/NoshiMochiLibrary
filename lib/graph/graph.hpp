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
  template<class C>
  struct maxflow_edge : public base_edge {
    C cap;
    std::size_t rev;
    maxflow_edge(int from, int to, C cap, std::size_t rev)
      : base_edge(from, to), cap(cap), rev(rev) {  }
  };

  template<class C>
  struct mcf_edge : public base_edge {
    C cap;
    C cost;
    std::size_t rev;
    mcf_edge(int from, int to, C cap, C cost, std::size_t rev)
      : base_edge(from, to), cap(cap), cost(cost), rev(rev) {  }
  };

  template<class T>
  struct directed_graph : public std::vector<std::vector<edge<T>>> {
    directed_graph(std::size_t n): std::vector<std::vector<edge<T>>>(n) { }
    void add_edge(const edge<T>& e) { this->at(e.from).push_back(e); }
  };

  template<class T>
  struct undirected_graph : public std::vector<std::vector<edge<T>>> {
    undirected_graph(std::size_t n): std::vector<std::vector<edge<T>>>(n) { }
    void add_edge(const edge<T>& e) { 
      this->at(e.from).push_back(e);
      edge<T> re = e;
      std::swap(re.from, re.to);
      this->at(e.to).push_back(re); 
    }
  };

  template<class C>
  struct maxflow_graph : public std::vector<std::vector<maxflow_edge<C>>> {
    maxflow_graph(std::size_t n): std::vector<std::vector<maxflow_edge<C>>>(n) {  }
    void add_edge(int from, int to, C cap, std::size_t rev_cap = 0) {
      this->at(from).push_back(maxflow_edge<C>(from, to, cap, this->at(to).size()));
      this->at(to).push_back(maxflow_edge<C>(to, from, rev_cap, this->at(from).size() - 1));
    }
  };

  template<class C>
  struct mcf_graph : public std::vector<std::vector<mcf_edge<C>>> {
    mcf_graph(std::size_t n) : std::vector<std::vector<mcf_edge<C>>>(n) {  } 
    void add_edge(int from, int to, C cap, C cost, std::size_t rev_cap = 0) {
      this->at(from).push_back(mcf_edge<C>(from, to, cap, cost, this->at(to).size()));
      this->at(to).push_back(mcf_edge<C>(to, from, rev_cap, -cost, this->at(from).size() - 1));
    }
  };
}

#endif
