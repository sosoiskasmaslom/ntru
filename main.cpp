
#include <iostream>
#include "polynom.h"
#include "algorithm.h"
using namespace std;

int main() {
    own::polynom fuck(3, 2);
    own::polynom society(3, 4);

    //fuck * society;
    (fuck * society).draw(std::cout);
    //(fuck + 3).draw(std::cout);

    return 0;
}
