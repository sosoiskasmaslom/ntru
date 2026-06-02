
#include <ostream>
#include <algorithm>
#include <random>
#include "algorithm.h"
using namespace own;


int own::ext_euclid(int f, int g, int p) {
    f = own::abs_mod(f, p);
    int x1 = 0, x2 = 1, tmp = 0, q = 0;
    for (; f != g;) {
        tmp = p;
        q   = f / p;
        p   = f%p;
        f   = tmp;

        tmp = x1;
        x1  = x2 - x1 * q;
        x2  = tmp;
    }

    return x2;
}

unsigned own::abs_mod(int f, int p)
{ return (f % p + p) % p; }


ntru::ntru(unsigned N, unsigned p, unsigned q)
: _N(N), _p(p), _q(q), _g(polynom(N))
{
    N_minus_one = own::polynom(_N+1, 0);
    N_minus_one[0] = -1; N_minus_one[-1] = 1;

    gen_f();
}

ntru::ntru(polynom f, unsigned p, unsigned q)
: _N(f.get_N()), _p(p), _q(q), _f(f), _g(polynom(f.get_N()))
{
    N_minus_one = own::polynom(_N+1, 0);
    N_minus_one[0] = -1; N_minus_one[-1] = 1;

    _F_p = _f.rev(N_minus_one, _p);
    _F_q = _f.rev(N_minus_one, _q);

    _h = (_F_q * _g).mod(N_minus_one).mod(_q);
}


void ntru::gen_f() {
    int mass[_N];
    for(int i = 0; i<_N; ++i)
    { mass[i] = i; }

    polynom tmp(_N, 0);
    std::mt19937 rng(std::random_device{}());

    for(;;) {
        unsigned d = own::randint(1, (_N-1)/2);
        std::shuffle(mass, mass+_N, rng);

        for(int i = 0; i<d; i++)
        { tmp[mass[i]] = 1; }

        for(int i = d; i<2*d; i++)
        { tmp[mass[i]] = -1; }

        if(tmp.rev(N_minus_one, _p).get_N() == _N)
        { _f = tmp; break; }
    }

    _F_p = _f.rev(N_minus_one, _p);
    _F_q = _f.rev(N_minus_one, _q);

    _h = (_F_q * _g).mod(N_minus_one).mod(_q);
}

const polynom& ntru::get_f() const
{ return _f; }

const polynom& ntru::get_h() const
{ return _h; }


polynom ntru::encrypt(const polynom& other) const {
    polynom r(_N); // уже случайный
    polynom salt = (r * _h * _p);

    return (salt + other).mod(N_minus_one).mod(_q);
}

polynom ntru::decrypt(const polynom& other) const {
    polynom a = (other * _f);

    for (unsigned i = 0; i < _N; i++) {
        int coef = (int)a[i];
        if (coef > (int)_q / 2)
            coef -= (int)_q;
        a[i] = (size_t)coef;
    }

    return (a * _F_p).mod(N_minus_one).mod(_p);
}
