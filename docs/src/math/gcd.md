---
layout: default
title: math-gcd
---

# gcd

最大公約数を求めます

```cpp
#include <cstddef>


namespace nimi{
    std::size_t gcd(std::size_t a, std::size_t b) {
    if(b == 0) return a;
    return gcd(b, a % b);
    }
}
```