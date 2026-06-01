
#include <iostream>
#include <random>
#include <chrono>
#include "polynom.h"
#include "algorithm.h"
using namespace own;


template<typename F>
void edit_v(own::size_t *v, unsigned N, F op) {
    for(own::size_t *end = v+N; v<end; op(v++)) {}
}



own::size_t own::max(own::size_t a, own::size_t b)
{ return (a>b) ? a : b; }

own::size_t own::min(own::size_t a, own::size_t b)
{ return (a<b) ? a : b; }

own::size_t own::pow(own::size_t a, own::size_t b)
{
    for(size_t c = a; b-1; --b)
    { a *= c; }

    return a;
}

own::size_t own::abs(own::size_t a)
{ return (a>=0) ? a : -1*a; }

int own::randint(int min, int max) {
    static std::mt19937 gen(
        std::chrono::steady_clock::now().time_since_epoch().count()
    );
    std::uniform_int_distribution<int> dist(min, max);
    return dist(gen);
}


polynom::polynom()
: polynom(5)
{}

polynom::polynom(unsigned N)
: _N(N), _vector(new size_t[N])
{
    for(int i = 0; i < get_N(); i++)
    { at(i) = own::randint(-1, 1); }
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
{ return *(_vector + own::abs_mod(i, get_N())); }

own::size_t& polynom::at(unsigned i)
{ return *(_vector + own::abs_mod(i, get_N())); }


unsigned polynom::get_N() const
{ return _N; }

own::size_t* polynom::get_v() const
{ return _vector; }

int polynom::get_d() const {
    for(int i = get_N()-1; i >= 0; --i)
        if (at(i) != 0) return i;
    return -1;
}


polynom& polynom::resize(unsigned n) {
    size_t *v = new size_t[n];
    for(int i = 0; n-i; ++i)
    { v[i] = (_N > i) ? at(i) : 0; }

    _N = n;
    delete[] _vector;
    _vector = v;

    return *this;
}

polynom& polynom::fit()
{ return resize(get_d()+1); }

polynom& polynom::mod(int p) {
    for(int i = 0; get_N()-i; ++i)
    { at(i) = own::abs_mod(at(i), p); }

    return *this;
}


polynom* polynom::division(const polynom& other) const {

    if (other.get_d() < 0 )
    { throw std::invalid_argument("Division by zero polynomial"); }

    int deg_a = this->get_d();
    int deg_b = other.get_d();
    int deg_c = deg_a - deg_b + 1;

    polynom *res = new polynom[2];
    *res      = polynom(deg_c, 0); // частное
    *(res+1)  = polynom(*this); // остаток от деления
    *(res+1) *= own::pow( other[other.get_d()], deg_c);

    if (deg_a < deg_b)
    { return res; }

    for(int i = deg_c-1; (i+1); --i) {
        (*res).at(i) = (*(res+1)).at((*(res+1)).get_d()) / other[other.get_d()];
        *(res+1) -= (other.mult_x(i) *= (*res).at(i));
    }

    return res;
}

polynom polynom::mult_x(int p) const {
    if (p == 0)
    { return *this; }

    if (get_d()+1 + p <= 0)
    { return polynom(1, 0); }

    polynom tmp(get_d()+1 + p, 0);
    for(int i = get_d(); (i+1) && (i+p+1); --i)
    { tmp.at(i+p) = at(i); }

    return tmp;
}

polynom polynom::mult(const polynom& other) const {
    if (other.get_d() < 0)
    { return polynom(1, 0); }

    polynom tmp(*this * other.at(0));
    for(int i = other.get_d(); i; --i)
    { tmp += (this->mult_x(i) *= other.at(i)); }

    return tmp.fit();
}

polynom polynom::rev(const polynom& other, size_t p) const {
    polynom first(other);
    polynom second(*this);

    polynom quotient;
    polynom x1(1, 1), x2(1, 0);

    polynom *tmp;

    for(; second.get_d(); ) {
        tmp = first.division(second);
        first = second;
        second = (*(tmp+1)).mod(p);
        quotient = (*tmp).mod(p);
        if (!second.get_d())
        { (quotient *= own::ext_euclid(second.at(0), 1, p)).mod(p); }
        delete[] tmp;

        tmp = new polynom(x1);
        x1 = (x2 - quotient.mult(x1)).mod(p);
        x2 = (*tmp).mod(p);
        delete tmp;

        //first.draw(std::cout);
        //second.draw(std::cout);
        //quotient.draw(std::cout);
        //x1.draw(std::cout);
        //x2.draw(std::cout);
        //std::cout << std::endl;
    }

    return x1.mod(p);
}


std::ostream& polynom::draw(std::ostream& out) const {
    for(unsigned i = 0; i < _N; i++) {
        if(i == 0) {
            if (at(i) < 0)
            { out << " - ";}
        }
        else if(at(i) >= 0) {
            out << " + ";
        } else {
            out << " - ";
        }
        out << "(x^" << i << ")*" << own::abs(at(i));
    }
    out << std::endl;

    return out;
}
