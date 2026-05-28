
#pragma once
#include "polynom.h"

namespace own {

    // Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
    int ext_euclid(int f, int k, int p);
    unsigned abs_mod(int f, int p);

    class ntru {
        unsigned _N, _p, _q;
        polynom _f, _h, _g, _F_q, _F_p;
        polynom N_minus_one;

    public:
        ntru(unsigned N, unsigned p, unsigned q);
        ntru(polynom f, unsigned p, unsigned q);

        void gen_f();
        const polynom& get_f() const;
        const polynom& get_h() const;

        polynom encrypt(const polynom& other) const;
        polynom decrypt(const polynom& other) const;

        polynom mark(size_t m) const;
        size_t umark(const polynom& m) const;
    };

}
