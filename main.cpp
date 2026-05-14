
#include <iostream>
#include "polynom.h"
using namespace std;

int main() {
    own::polynom fuck {15, 0};
    fuck.mult_x(-9).draw(cout);

//for(int i = 0; i<9; ++i)
//        fuck.mult_x(i).draw(cout);

    return 0;
}
