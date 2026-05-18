
#pragma once
#include "polynom.h"

namespace own {

    class ntru {
        unsigned _N;
        unsigned  _p,  _q;
        polynom   _f, _g, _h;
        polynom _F_q, _F_p;

        polynom N_minus_one;
    public:
        ntru(
            unsigned N,
            unsigned p,
            unsigned q
        );
        ntru(
            const polynom& f,
            unsigned p,
            unsigned q
        );

        const polynom& get_f() const;
        const polynom& get_h() const;

        void encrypt(polynom& other) const;
        void decrypt(polynom& other) const;

        polynom mark(int i) const;
        int umark(const polynom& other) const;
    };

}
