
#include "algorithm.h"
#include "polynom.h"
using namespace own;


ntru::ntru(unsigned N, unsigned p, unsigned q)
: ntru(polynom(N), p, q)
{}

ntru::ntru(const polynom& f, unsigned p, unsigned q)
: _N(f.get_N()), _p(p), _q(q),
  _f(f), _g(polynom(_N))
{
    N_minus_one = polynom {_N, 0};
    N_minus_one[0] = N_minus_one[_N-1] = 1;

    _F_q = _f.mod(N_minus_one, _q);
    _F_p = _f.mod(N_minus_one, _p);

    _h = (_F_q * _g).mod(N_minus_one, _q);
}

const polynom& ntru::get_f() const
{ return _f; }

const polynom& ntru::get_h() const
{ return _h; }

void ntru::encrypt(polynom& other) const {
    polynom r(_N); // уже случайный
    polynom rph = (r * (own::size_t)_p * _h).mod(N_minus_one, _q);
    polynom m   = other.mod(N_minus_one, _q);
    other = (rph + m).mod(N_minus_one, _q);
}

void ntru::decrypt(polynom& other) const {
    polynom a = (other * _f).mod(N_minus_one, _q);

    // центрируем из [0, q) в (-q/2, q/2]
    for (unsigned i = 0; i < _N; i++) {
        int coef = (int)a[i];
        if (coef > (int)_q / 2)
            coef -= (int)_q;
        a[i] = (size_t)coef;
    }

    other = (a * _F_p).mod(N_minus_one, _p);
}

polynom ntru::mark(int i) const {
    polynom result(_N);
    for (unsigned j = 0; j < _N; ++j)
        result[j] = 0;

    bool negative = i < 0;
    unsigned val = negative ? (unsigned)(-i) : (unsigned)i;

    // записываем цифры по основанию p
    unsigned j = 0;
    while (val > 0 && j < _N - 1) { // -1 — резервируем старший коэф для знака
        result[j++] = val % _p;
        val /= _p;
    }

    // знак в старшем коэффициенте
    result[_N - 1] = negative ? 1 : 0;

    if (val > 0)
        throw std::overflow_error("Value too large for polynom of degree _N with base _p");

    return result;
}

int ntru::umark(const polynom& other) const {
    // читаем знак из старшего коэффициента
    bool negative = other[_N - 1] != 0;

    int result = 0;
    int base = 1;
    for (unsigned j = 0; j < _N - 1; ++j) {
        result += (int)other[j] * base;
        base *= (int)_p;
    }

    return negative ? -result : result;
}
