#ifndef NIMI_DATASTRUCTURE_HEAP_PAIRINGHEAP
#define NIMI_DATASTRUCTURE_HEAP_PAIRINGHEAP

#include <cassert>
#include <cstddef>
#include <functional>
#include <memory>
#include <utility>

namespace nimi {

template <class T, class Compare = std::less<T>> class pairing_heap {

public:
  using value_type = T;
  using const_reference = const value_type &;
  using size_type = std::size_t;
  using value_compare = Compare;

private:
  class node_type;
  using node_ptr = std::unique_ptr<node_type>;

  class node_type {
  public:
    node_ptr next, head;
    value_type value;
    template <class... Args>
    node_type(Args &&... args)
        : next(), head(), value(std::forward<Args>(args)...) {}
  };

  template <class... Args> static node_ptr make_node(Args &&... args) {
    return std::make_unique<node_type>(std::forward<Args>(args)...);
  }
  static bool has_object(const node_ptr &ptr) noexcept {
    return static_cast<bool>(ptr);
  }

  node_ptr root;

protected:
  value_compare comp;

private:
  node_ptr merge(node_ptr &&x, node_ptr &&y) const {
    if (!has_object(x)) {
      return std::move(y);
    } else if (!has_object(y)) {
      return std::move(x);
    } else if (comp(y->value, x->value)) {
      y->next = std::move(x->head);
      x->head = std::move(y);
      return std::move(x);
    } else {
      x->next = std::move(y->head);
      y->head = std::move(x);
      return std::move(y);
    }
  }
  node_ptr merge_list(node_ptr &&list) const {
    node_ptr pairs;
    while (has_object(list) && has_object(list->next)) {
      node_ptr second = std::move(list->next);
      node_ptr tail = std::move(second->next);
      list = merge(std::move(list), std::move(second));
      list->next = std::move(pairs);
      pairs = std::move(list);
      list = std::move(tail);
    }
    while (has_object(pairs)) {
      node_ptr tail = std::move(pairs->next);
      list = merge(std::move(list), std::move(pairs));
      pairs = std::move(tail);
    }
    return std::move(list);
  }

  void merge_to_root(node_ptr &&ptr) {
    root = merge(std::move(root), std::move(ptr));
  }

public:
  pairing_heap() = default;
  // 比較関数から構築
  explicit pairing_heap(const value_compare &x) : root(), comp(x) {}
  // [first, last) の要素から構築
  template <class InputIterator>
  pairing_heap(InputIterator first, const InputIterator last,
               const value_compare &x = value_compare())
      : root(), comp(x) {
    for (; first != last; ++first) {
      push(*first);
    }
  }

  // 空かどうかを判定
  bool empty() const noexcept { return !has_object(root); }
  // 最大要素への参照
  const_reference top() const noexcept {
    assert(("called pairing_heap::top on an empty queue", !empty()));
    return root->value;
  }

  // x を追加
  void push(const value_type &x) { merge_to_root(make_node(x)); }
  // x を move して追加
  void push(value_type &&x) { merge_to_root(make_node(std::move(x))); }
  // args から直接構築で追加
  template <class... Args> void emplace(Args &&... args) {
    merge_to_root(make_node(std::forward<Args>(args)...));
  }
  // 最大要素の削除
  void pop() {
    assert(("called pairing_heap::pop on an empty queue", !empty()));
    root = merge_list(std::move(root->head));
  }
  // x の全要素を追加
  void meld(pairing_heap &&x) { merge_to_root(std::move(x.root)); }
};

} // namespace nimi

#endif
