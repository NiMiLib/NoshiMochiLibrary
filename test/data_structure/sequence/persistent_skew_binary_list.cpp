#include <lib/data_structure/sequence/persistent_skew_binary_list>
#include <cassert>
#include <cstddef>
#include <limits>
#include <random>
#include <string>
#include <vector>

namespace nimi {

class checker {
public:
  std::vector<int> vec;
  persistent_skew_binary_list<int> list;

  checker() : list(), vec() {}
  void check() const {
    assert(list.is_empty() == vec.empty());
    if (!vec.empty()) {
      assert(list.head() == vec.front());
    }
    for (std::size_t i = 0; i != vec.size(); ++i) {
      assert(list.lookup(i) == vec[i]);
    }
  }
  checker cons(const int &new_value) const {
    checker ret;
    ret.list = list.cons(new_value);
    ret.vec = vec;
    ret.vec.insert(ret.vec.begin(), new_value);
    return std::move(ret);
  }
  checker tail() const {
    checker ret;
    ret.list = list.tail();
    ret.vec = vec;
    ret.vec.erase(ret.vec.begin());
    return std::move(ret);
  }
  checker update(const std::size_t index, const int &new_value) const {
    checker ret;
    ret.list = list.update(index, new_value);
    ret.vec = vec;
    ret.vec[index] = new_value;
    return std::move(ret);
  }
};

void test() {
  const std::size_t q = 3000;
  std::default_random_engine engine(91);
  std::vector<checker> past(1);
  for (std::size_t i = 0; i != q; ++i) {
    std::size_t old_i = i;
    while (old_i != 0) {
      if (std::uniform_int_distribution<int>(0, 2)(engine) == 0) {
        break;
      } else {
        --old_i;
      }
    }
    const checker &old = past[old_i];
    std::vector<std::string> ops;
    ops.emplace_back("cons");
    ops.emplace_back("cons");
    ops.emplace_back("cons");
    if (!old.vec.empty()) {
      ops.emplace_back("tail");
      ops.emplace_back("update");
    }
    const std::string &op = ops[std::uniform_int_distribution<std::size_t>(
        0, ops.size() - 1)(engine)];
    if (op == "cons") {
      past.push_back(old.cons(std::uniform_int_distribution<int>(
          std::numeric_limits<int>::lowest(),
          std::numeric_limits<int>::max())(engine)));
    } else if (op == "tail") {
      past.push_back(old.tail());
    } else if (op == "update") {
      past.push_back(old.update(std::uniform_int_distribution<std::size_t>(
                                    0, old.vec.size() - 1)(engine),
                                std::uniform_int_distribution<int>(
                                    std::numeric_limits<int>::lowest(),
                                    std::numeric_limits<int>::max())(engine)));
    } else {
      assert(false);
    }
    past.back().check();
  }
  return;
}

} // namespace nimi

int main() {
  nimi::test();
  return 0;
}
