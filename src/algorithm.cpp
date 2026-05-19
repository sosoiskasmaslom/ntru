
#include <stdexcept>

#include "algorithm.h"
#include "polynom.h"
#include "euclid.h"
using namespace own;


own::polynom own::gen_f(
        unsigned N, int d,
        const polynom& nmo, int p, int q
    ) {
    polynom tmp {N, 0};
    int run[] = {-1, 1};

    std::cerr << "and here too" << std::endl;
    while (1) {
        for(int i = 0; i<N; ++i)
            tmp[i] = 0;

        for(auto r: run) {
            for(int i=0, j; i<d; ) {
                j = randint(0, N-1);
                if(tmp[j] != 0) {
                    continue;
                } else {
                    tmp[j] = 1;
                    ++i;
                }
            }
        }

        try {
            poly_inverse(tmp, nmo, p).draw(std::cerr);
            poly_inverse(tmp, nmo, q).draw(std::cerr);
            break;
        } catch(const std::exception& e) {
            std::cerr << "fcuk" << std::endl;
        }
    }
    std::cerr << "circle is ended" << std::endl;

    return tmp;
}


ntru::ntru(unsigned N, unsigned p, unsigned q)
: ntru(polynom(N), p, q)
{}

ntru::ntru(const polynom& f, unsigned p, unsigned q)
: _N(f.get_N()), _p(p), _q(q),
  _f(f), _g(polynom(_N))
{
    N_minus_one     = polynom {_N+1, 0};
    N_minus_one[0]  = -1;
    N_minus_one[_N] = 1;

    std::cerr << "i was here" << std::endl;
    _f = gen_f(_N, 2, N_minus_one, p, q);
    std::cerr << "finished gen" << std::endl;

    _F_q = poly_inverse(_f, N_minus_one, _q);
    _F_p = poly_inverse(_f, N_minus_one, _p);
    std::cerr << "no mother?" << std::endl;

    (_F_q * _f).draw(std::cerr);
    _h = poly_inverse(_F_q * _g, N_minus_one, _q);
    std::cerr << "it isnt public key" << std::endl;
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
