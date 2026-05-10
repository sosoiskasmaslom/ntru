
#include <iostream>
#include "polynom.h"
using namespace std;

int main() {
    own::size_t v1[] = {0, 1, 1, 0, -1};
    own::size_t v2[] = {2, 8, 1, 4,  4};
    own::polynom fuck {5, v1};
    own::polynom society {5, v2};
    own::polynom res {fuck * society};

    own::size_t *pointer = res.get_v();
    for(int i = 0; i<5; ++i)
        cout << *(pointer++) << ' ';
    cout << endl;

    return 0;
}
