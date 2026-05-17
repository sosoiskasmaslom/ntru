
#include <ostream>
#include "euclid.h"

// Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
// Возвращает x такое что a*x ≡ 1 (mod p)
long long own::mod_inverse(long long a, long long p) {
    a = ((a % p) + p) % p; // нормализуем на случай отрицательного a

    long long old_r = p, r = a;
    long long old_x = 0, x = 1;

    while (r != 0) {
        long long q = old_r / r;
        long long tmp;

        tmp = r;   r   = old_r - q * r;   old_r = tmp;
        tmp = x;   x   = old_x - q * x;   old_x = tmp;
    }

    // old_r — это gcd(a, p)
    if (old_r != 1)
        throw std::runtime_error("No modular inverse: gcd(a, p) != 1");

    return ((old_x % p) + p) % p;
}
