
#include <iostream>
#include "polynom.h"
using namespace std;

int main() {
    own::polynom fuck {3, 5};
    fuck /= 4;
    for(int i=0; i<3; ++i)
    { cout << fuck[i] << ' '; }
    cout << endl;

    return 0;
}
