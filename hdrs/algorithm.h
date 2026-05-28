
#pragma once
#include "polynom.h"

namespace own {

    // Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
    int ext_euclid(int f, int k, int p);
    unsigned abs_mod(int f, int p);

}
