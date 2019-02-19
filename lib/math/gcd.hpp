#ifndef NIMILIB_MATH_GCD
#define NIMILIB_MATH_GCD

#include <cstddef>


namespace nimi{
    std::size_t gcd(std::size_t a, std::size_t b) {
    if(b == 0) return a;
    return gcd(b, a % b);
    }
}

#endif