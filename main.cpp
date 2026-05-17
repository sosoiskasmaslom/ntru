
#include <iostream>
#include "polynom.h"
#include "euclid.h"
using namespace std;

int main() {
    int a[] = {1, 1, 1, 1};
    int b[] = {1, 1};

    own::polynom pa(4, a);
    own::polynom pb(2, b);

    own::polynom q = pa.div_mod(pb, 5);
    own::polynom r = pa.rem_mod(pb, 5);

    q.draw(cout) << endl; // ожидаем: 1 + x²  →  {1, 0, 1}
    r.draw(cout) << endl; // ожидаем: 0  →  {0}    return 0;

    return 0;
}
