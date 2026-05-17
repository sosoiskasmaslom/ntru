
#include <ostream>
#include "polynom.h"
#include "euclid.h"
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

int polynom::get_d() const {
    for (int i = get_N() - 1; i >= 0; --i)  // _N-1, не _N
        if (at(i) != 0)
            return i;
    return -1;
}

polynom polynom::mult_x(int p) const {
    if(p == 0)
    { return *this; }

    unsigned N = this->_N + p;
    polynom tmp {N, 0};

    for(unsigned i=N; i>p; --i)
    { tmp[i] = at(min(i, i-p)); }

    return tmp;
}

polynom polynom::div_mod(const polynom& other, size_t p) const {
    int deg_a = this->get_d();
    int deg_b = other.get_d();

    if (deg_b < 0)
        throw std::invalid_argument("Division by zero polynomial");

    if (deg_a < deg_b)
        return polynom(1); // нулевой полином из 1 элемента

    unsigned quot_size = (unsigned)(deg_a - deg_b + 1);
    polynom quotient(quot_size);
    for (unsigned i = 0; i < quot_size; ++i)
        quotient[i] = 0;

    polynom remainder(*this);
    // приводим remainder по модулю p
    for (unsigned i = 0; i < remainder.get_N(); ++i)
        remainder[i] = ((long long)remainder[i] % p + p) % p;

    size_t lead_b = ((long long)other[deg_b] % p + p) % p;
    long long inv_lead = own::mod_inverse((long long)lead_b, (long long)p);

    for (int i = deg_a - deg_b; i >= 0; --i) {
        long long coef = ((long long)remainder[i + deg_b] * inv_lead) % p;
        quotient[i] = (size_t)coef;

        for (int j = 0; j <= deg_b; ++j) {
            long long sub = (long long)coef * (long long)other[j] % p;
            remainder[i + j] = (((long long)remainder[i + j] - sub) % p + p) % p;
        }
    }

    return quotient;
}

polynom polynom::rem_mod(const polynom& other, size_t p) const {
    int deg_a = this->get_d();
    int deg_b = other.get_d();

    if (deg_b < 0)
        throw std::invalid_argument("Division by zero polynomial");

    if (deg_a < deg_b) {
        // просто приводим *this по модулю p
        polynom result(*this);
        for (unsigned i = 0; i < result.get_N(); ++i)
            result[i] = ((long long)result[i] % p + p) % p;
        return result;
    }

    polynom remainder(*this);
    for (unsigned i = 0; i < remainder.get_N(); ++i)
        remainder[i] = ((long long)remainder[i] % p + p) % p;

    size_t lead_b = ((long long)other[deg_b] % p + p) % p;
    long long inv_lead = own::mod_inverse((long long)lead_b, (long long)p);

    for (int i = deg_a - deg_b; i >= 0; --i) {
        long long coef = ((long long)remainder[i + deg_b] * inv_lead) % p;

        for (int j = 0; j <= deg_b; ++j) {
            long long sub = coef * (long long)other[j] % p;
            remainder[i + j] = (((long long)remainder[i + j] - sub) % p + p) % p;
        }
    }

    // обрезаем до фактической степени остатка
    int rem_deg = remainder.get_d();
    if (rem_deg < 0)
        return polynom(1); // нулевой полином

    polynom result((unsigned)rem_deg + 1);
    for (int i = 0; i <= rem_deg; ++i)
        result[i] = remainder[i];

    return result;
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

