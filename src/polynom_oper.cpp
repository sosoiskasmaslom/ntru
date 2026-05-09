
#include <iostream>
#include "polynom.h"
using namespace own;


template<typename F>
void edit_v(own::size_t *v, unsigned N, F op) {
    for(own::size_t *end = v+N; v<end; op(v++)) {}
}


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

polynom& polynom::operator*=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v *= x; });
    return *this;
}

polynom& polynom::operator/=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v /= x; });
    return *this;
}

polynom& polynom::operator%=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v %= x; });
    return *this;
}


polynom& polynom::operator+=(polynom other) {
    for(
        size_t *t=_vector, *o=other.get_v();
        t < _vector+min(_N, other.get_N());
        *(t++) += *(o++)
       ) {}
    return *this;
}

polynom& polynom::operator-=(polynom other)
{ return *this += other *= -1; }


own::size_t  polynom::operator[](unsigned i) const
{ return *(_vector+i); }

own::size_t& polynom::operator[](unsigned i)
{ return *(_vector+i); }
