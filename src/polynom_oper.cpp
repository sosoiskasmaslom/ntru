
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


polynom polynom::operator+(polynom other)
{ return other += *this; }

polynom polynom::operator-(polynom other)
{ return other -= *this; }


polynom polynom::operator*(polynom other) {
    if (this->_N != other.get_N())
    { return *this; }

    polynom tmp {_N, 0};
    for(unsigned k=0; k<_N; ++k) {
        for(unsigned i=0; i<k+1; ++i)
        { tmp[k] += this->at(i) * other.at(k-i); }

        for(unsigned i=k+1; i<_N; ++i)
        { tmp[k] += this->at(i) * other.at(_N+k-i); }
    }

    return tmp;
}

//polynom polynom::operator/(polynom other) {
//    size_t N = abs(this->_N - other.get_N());
//    size_t *v = new size_t[N];
//
//
//}


own::size_t  polynom::operator[](unsigned i) const
{ return this->at(i); }

own::size_t& polynom::operator[](unsigned i)
{ return this->at(i); }
