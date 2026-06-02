
#include <ostream>
#include <algorithm>
#include "polynom.h"
using namespace own;


polynom& polynom::operator=(const polynom& other) {
    if (this == &other)
    { return *this; }

    delete[] _vector;

    _N = other.get_N();
    _vector = new size_t[_N];
    std::copy(
        other.get_v(),
        other.get_v() + other.get_N(),
        get_v()
    );

    return *this;
}


polynom& polynom::operator+=(size_t a) {
    *_vector += a;
    return *this;
}

polynom& polynom::operator-=(size_t a)
{ return *this+=(-1*a); }

polynom& polynom::operator*=(size_t a) {
    std::for_each(
        get_v(),
        get_v() + get_N(),
        [a](size_t &x){ x *= a; }
    );
    return *this;
}

polynom& polynom::operator/=(size_t a) {
    std::for_each(
        get_v(),
        get_v() + get_N(),
        [a](size_t &x){ x /= a; }
    );
    return *this;
}

polynom& polynom::operator%=(size_t a) {
    std::for_each(
        get_v(),
        get_v() + get_N(),
        [a](size_t &x){ x %= a; }
    );
    return *this;
}


polynom& polynom::operator+=(const polynom& other) {
    if(this->get_N() < other.get_N())
    { resize((int)(other.get_N())); }

    for(int i = other.get_d(); i+1; --i)
    { at(i) += other.at(i); }

    return this->fit();
}

polynom& polynom::operator-=(const polynom& other) {
    if(this->get_N() < other.get_N())
    { resize((int)(other.get_N())); }

    for(int i = other.get_d(); i+1; --i)
    { at(i) -= other.at(i); }

    return this->fit();
}

polynom& polynom::operator*=(const polynom& other) {
    if (this->get_N() != other.get_N())
    { return *this; }

    size_t *tmp = new size_t[get_N()];
    for(int i = 0; i<get_N(); ++i)
    { tmp[i] = 0; }

    for(unsigned k=0; k<get_N(); ++k) {
        for(unsigned i=0; i<k+1; ++i)
        { tmp[k] += this->at(i) * other.at(k-i); }

        for(unsigned i=k+1; i<get_N(); ++i)
        { tmp[k] += this->at(i) * other.at(_N+k-i); }
    }

    delete[] _vector;
    _vector = tmp;

    return *this;
}


polynom polynom::operator+(size_t a) const
{ return own::polynom(*this) += a; }

polynom polynom::operator-(size_t a) const
{ return own::polynom(*this) -= a; }

polynom polynom::operator*(size_t a) const
{ return own::polynom(*this) *= a; }

polynom polynom::operator/(size_t a) const
{ return own::polynom(*this) /= a; }

polynom polynom::operator%(size_t a) const
{ return own::polynom(*this) %= a; }


polynom polynom::operator+(const polynom& other) const
{ return own::polynom(*this) += other; }

polynom polynom::operator-(const polynom& other) const
{ return own::polynom(*this) -= other; }

polynom polynom::operator*(const polynom& other) const
{ return own::polynom(*this) *= other; }


own::size_t  polynom::operator[](unsigned i) const
{ return this->at(i); }

own::size_t& polynom::operator[](unsigned i)
{ return this->at(i); }
