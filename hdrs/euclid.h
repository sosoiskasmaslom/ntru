
#pragma once
#include <iostream>
#include "polynom.h"

namespace own {

    // Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
    // Возвращает x такое что a*x ≡ 1 (mod p)
    long long mod_inverse(long long a, long long p);

    polynom poly_inverse(const polynom& f, polynom mod_poly, int p);

}
