
#include <iostream>
#include "polynom.h"
#include "euclid.h"
#include "algorithm.h"
using namespace std;

// int main() {
//     int a[] = {1, 1, -1, 1, -1};
//     int b[] = {-1, 0, 0, 0, 0, 1};
//
//     own::polynom pa(5, a);
//     own::polynom pb(6, b);
//
//     own::polynom q = pa.div_mod(pb, 11);
//     // own::polynom r = pa.rem_mod(pb, 5);
//
//     q.draw(cout) << endl; // ожидаем: 1 + x²  →  {1, 0, 1}
//     // r.draw(cout) << endl; // ожидаем: 0  →  {0}    return 0;
//
//     return 0;
// }

int main() {
    own::ntru test{5, 3, 11};
    own::polynom fuck = test.mark(12);
    fuck.draw(cout) << "before encrypt" << endl;

    test.encrypt(fuck);

    fuck.draw(cout) << "encrypted" << endl;

    test.decrypt(fuck);

    fuck.draw(cout) << "after encrypt" << endl;

    cout << "number is " << test.umark(fuck) << endl;

    return 0;
}
