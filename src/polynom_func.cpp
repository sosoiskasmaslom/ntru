
#include <iostream>
#include <random>
#include <chrono>
#include "polynom.h"
#include "algorithm.h"
using namespace own;


template<typename F>
void edit_v(own::size_t *v, unsigned N, F op) {
    for(own::size_t *end = v+N; v<end; op(*(v++))) {}
}


own::size_t own::max(own::size_t a, own::size_t b)
{ return (a>b) ? a : b; }

own::size_t own::min(own::size_t a, own::size_t b)
{ return (a<b) ? a : b; }

own::size_t own::abs(own::size_t a)
{ return (a>=0) ? a : -1*a; }

int own::randint(int min, int max) {
    static std::mt19937 gen(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}


polynom::polynom(unsigned N)
: _N(N), _vector(new size_t[N])
{
    for(int i = 0; i < get_N(); i++)
    { at(i) = own::randint(0, 1); }
}

polynom::polynom(unsigned N, size_t a)
: _N(N), _vector(new size_t[N])
{
    for(int i = 0; i < get_N(); i++)
    { at(i) = a; }
}

polynom::polynom(unsigned N, size_t *vector)
: _N(N), _vector(new size_t[N])
{
    for(int i = 0; i < get_N(); i++)
    { at(i) = vector[i]; }
}

polynom::polynom(const polynom& other)
: _N(other.get_N()), _vector(new size_t[other.get_N()])
{
    for(int i = 0; i < get_N(); i++)
    { at(i) = other[i]; }
}


polynom::~polynom()
{ delete[] _vector; }


own::size_t polynom::at(unsigned i) const
{ return *(_vector + own::abs_mod(i, _N)); }

own::size_t& polynom::at(unsigned i)
{ return *(_vector + own::abs_mod(i, _N)); }


unsigned polynom::get_N() const
{ return _N; }

own::size_t* polynom::get_v() const
{ return _vector; }

int polynom::get_d() const {
    for(int i = get_N()-1; i >= 0; --i)
        if (at(i) != 0) return i;
    return -1;
}


polynom polynom::rev(const polynom& other, size_t p) const {
    int deg_a = this->get_d();
    int deg_b = other.get_d();

    if (deg_b < 0 )
    { throw std::invalid_argument("Division by zero polynomial"); }

    if (deg_a < deg_b) {
        polynom result(*this);
        edit_v(result.get_v(), result.get_N(), [p](size_t &v){ v = own::abs_mod(v, p); });
        return result;
    }

    polynom remainder(*this);
    edit_v(remainder.get_v(), remainder.get_N(), [p](size_t &v){ v = own::abs_mod(v, p); });

    size_t lead_b = own::abs_mod(other[deg_b], p);
    size_t inv_lead = own::ext_euclid(lead_b, 1, p);

    for (int i = deg_a - deg_b; i >= 0; --i) {
        size_t coef = (remainder[i + deg_b] * inv_lead) % p;

        for (int j = 0; j <= deg_b; ++j) {
            size_t sub = coef * other[j] % p;
            remainder[i + j] = own::abs_mod((remainder[i + j] - sub), p);
        }
    }

    int rem_deg = remainder.get_d();
    if (rem_deg < 0) return polynom(1);

    polynom result(rem_deg + 1);
    for (int i = 0; i <= rem_deg; ++i)
    { result[i] = remainder[i]; }

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
