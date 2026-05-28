
#include <iostream>
#include "polynom.h"
#include "algorithm.h"
using namespace std;

int main() {
    own::polynom nmo(6, 0);
    nmo[0] = -1; nmo[-1] = 1;
    nmo.draw(cout);

    own::polynom fuck(5, 2);
    fuck.draw(cout);
    fuck.rev(nmo, 3).draw(cout);

    return 0;
}
