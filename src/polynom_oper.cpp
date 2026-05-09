
#include <iostream>
#include "polynom.h"
using namespace own;

polynom& polynom::operator=(const polynom& other) {
    if (this == &other)
    { return *this; }

    delete[] _vector;

    _N = other.get_N();
    _vector = new size_t[_N];
    for(
        size_t *t=_vector, *o=other.get_v();
        t < _vector+_N;
        *(t++) = *(o++)
    ) {}

    return *this;
}


polynom& polynom::operator+=(size_t x) {
    *_vector += x;
    return *this;
}

polynom& polynom::operator-=(size_t x)
{ return *this+=(-1*x); }


