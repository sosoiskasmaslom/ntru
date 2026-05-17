
#pragma once
#include <iostream>

namespace own {
    // Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
    // Возвращает x такое что a*x ≡ 1 (mod p)
    long long mod_inverse(long long a, long long p);
}
