
#include <ostream>
#include "polynom.h"
using namespace own;

own::size_t own::max(own::size_t a, own::size_t b)
{ return (a>b) ? a : b; }

own::size_t own::min(own::size_t a, own::size_t b)
{ return (a<b) ? a : b; }

own::size_t own::abs(own::size_t a)
{ return (a>=0) ? a : -1*a; }


polynom::polynom()
: _N(0), _vector(new size_t[_N])
{}

polynom::polynom(unsigned N)
: own::polynom(N, 0)
{}

polynom::polynom(unsigned N, size_t a)
: _N(N), _vector(new size_t[_N])
{ for(size_t *t=_vector; t<_vector+_N; *(t++)=a) {} }

polynom::polynom(unsigned N, size_t *vector)
: _N(N), _vector(new size_t[_N])
{
    for(
        size_t *t=_vector, *o=vector;
        t<_vector+_N;
        *(t++)=*(o++)
    ) {}
}

polynom::polynom(const polynom& other)
: _N(other.get_N()), _vector(new size_t[_N])
{
    for(
        size_t *t=_vector, *o=other.get_v();
        t<_vector+_N;
        *(t++)=*(o++)
    ) {}
}

polynom::~polynom()
{ delete[] _vector; }

own::size_t polynom::at(unsigned i) const
{ return (i < _N) ? *(_vector+i) : *(_vector+i-_N); }

own::size_t& polynom::at(unsigned i)
{ return *(_vector+i); }

unsigned polynom::get_N() const
{ return _N; }

own::size_t* polynom::get_v() const
{ return _vector; }

polynom polynom::mult_x(int p) const {
    if(p == 0)
    { return *this; }

    unsigned N = this->_N + p;
    polynom tmp {N, 0};

    for(unsigned i=N; i>p; --i)
    { tmp[i] = at(min(i, i-p)); }

    return tmp;
}

std::ostream& polynom::draw(std::ostream& out) const {
    for(unsigned i = 0; i < _N; i++) {
        if(i == 0) {}
        else if(at(i) >= 0) {
            out << " + ";
        } else {
            out << " - ";
        }
        out << "(x^" << i << ")*" << at(i);
    }
    out << std::endl;

    return out;
}
