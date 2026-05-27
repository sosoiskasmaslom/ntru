
#include "algorithm.h"
using namespace own;

int own::ext_euclid(int f, int g, int p) {
    int x1 = 0, x2 = 1, tmp = 0, q = 0;
    for (; f != g;) {
        tmp = p;
        q   = f / p;
        p   = f%p;
        f   = tmp;

        tmp = x1;
        x1  = x2 - x1 * q;
        x2  = tmp;
    }

    return x2;
}
