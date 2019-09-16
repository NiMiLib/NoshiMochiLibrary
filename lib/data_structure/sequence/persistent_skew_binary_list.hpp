#ifndef NIMI_DATASTRUCTURE_SEQ_PSKEWBINLIST
#define NIMI_DATASTRUCTURE_SEQ_PSKEWBINLIST

#include <cstddef>
#include <memory>
#include <utility>

namespace nimi {

template <class T, class Size = std::size_t> class persistent_skew_binary_list {
  class tree_type;
  using tree_ptr = std::shared_ptr<const tree_type>;
  template <class... Args> static tree_ptr make_tree(Args &&... args) {
    return std::make_shared<tree_type>(std::forward<Args>(args)...);
  }
  class tree_type {
  public:
    T value;
    tree_ptr left;
    tree_ptr right;
    tree_type(const T &value, const tree_ptr &left, const tree_ptr &right)
        : value(value), left(left), right(right) {}
    const T &lookup(const Size &size, const Size &index) const {
      if (index == static_cast<Size>(0)) {
        return value;
      } else {
        const Size rem_index = index - static_cast<Size>(1);
        const Size child_size = size / static_cast<Size>(2);
        if (rem_index < child_size) {
          return left->lookup(child_size, rem_index);
        } else {
          return right->lookup(child_size, rem_index - child_size);
        }
      }
    }
    tree_ptr update(const Size &size, const Size &index,
                    const T &new_value) const {
      if (index == static_cast<Size>(0)) {
        return make_tree(new_value, left, right);
      } else {
        const Size rem_index = index - static_cast<Size>(1);
        const Size child_size = size / static_cast<Size>(2);
        if (rem_index < child_size) {
          return make_tree(
              value, left->update(child_size, rem_index, new_value), right);
        } else {
          return make_tree(
              value, left,
              right->update(child_size, rem_index - child_size, new_value));
        }
      }
    }
  };
  class digit_type;
  using digit_ptr = std::shared_ptr<const digit_type>;
  template <class... Args> static digit_ptr make_digit(Args &&... args) {
    return std::make_shared<digit_type>(std::forward<Args>(args)...);
  }
  class digit_type {
  public:
    Size size;
    tree_ptr tree;
    digit_ptr next;
    digit_type(const Size &size, const tree_ptr &tree, const digit_ptr &next)
        : size(size), tree(tree), next(next) {}
    const T &lookup(const Size &index) const {
      if (index < size) {
        return tree->lookup(size, index);
      } else {
        return next->lookup(index - size);
      }
    }
    digit_ptr update(const Size &index, const T &new_value) const {
      if (index < size) {
        return make_digit(size, tree->update(size, index, new_value), next);
      } else {
        return make_digit(size, tree, next->update(index - size, new_value));
      }
    }
  };

  digit_ptr root;

  explicit persistent_skew_binary_list(const digit_ptr &root) : root(root) {}

public:
  persistent_skew_binary_list() : root() {}

  bool is_empty() const { return !static_cast<bool>(root); }
  persistent_skew_binary_list cons(const T &new_value) const {
    if (root && root->next && root->size == root->next->size) {
      return persistent_skew_binary_list(
          make_digit(static_cast<Size>(1) + root->size + root->next->size,
                     make_tree(new_value, root->tree, root->next->tree),
                     root->next->next));
    } else {
      return persistent_skew_binary_list(make_digit(
          static_cast<Size>(1), make_tree(new_value, nullptr, nullptr), root));
    }
  }
  const T &head() const { return root->tree->value; }
  persistent_skew_binary_list tail() const {
    if (root->size == static_cast<Size>(1)) {
      return persistent_skew_binary_list(root->next);
    } else {
      const Size &child_size = root->size / static_cast<Size>(2);
      return persistent_skew_binary_list(
          make_digit(child_size, root->tree->left,
                     make_digit(child_size, root->tree->right, root->next)));
    }
  }
  const T &lookup(const Size &index) const { return root->lookup(index); }
  persistent_skew_binary_list update(const Size &index,
                                     const T &new_value) const {
    return persistent_skew_binary_list(root->update(index, new_value));
  }
};

} // namespace nimi

#endif
