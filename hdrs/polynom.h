
#pragma once

namespace own {

    using size_t = int;

    size_t max(size_t a, size_t b);
    size_t min(size_t a, size_t b);

    class polynom {
        size_t *_vector;
        unsigned _N;
    public:
        polynom();
        polynom(unsigned N);
        polynom(unsigned N, size_t a);
        polynom(unsigned N, size_t *vector);
        polynom(const polynom& other);

        ~polynom();

        polynom& operator=(const polynom& other);

        polynom& operator+=(size_t x);
        polynom& operator-=(size_t x);
        polynom& operator*=(size_t x);
        polynom& operator/=(size_t x);
        polynom& operator%=(size_t x);

        polynom& operator+=(const polynom& other);
        polynom& operator-=(const polynom& other);
        polynom& operator*=(const polynom& other);
        polynom& operator/=(const polynom& other);
        polynom& operator%=(const polynom& other);

        polynom operator+(size_t x);
        polynom operator-(size_t x);
        polynom operator*(size_t x);
        polynom operator/(size_t x);
        polynom operator%(size_t x);

        polynom operator+(const polynom& other);
        polynom operator-(const polynom& other);
        polynom operator*(const polynom& other);
        polynom operator/(const polynom& other);
        polynom operator%(const polynom& other);

        size_t  operator[](unsigned int i) const;
        size_t& operator[](unsigned int i);

        size_t  at(unsigned i) const;
        size_t& at(unsigned i);

        unsigned get_N() const;
        size_t* get_v() const;

        polynom mod(int x);
        polynom mod(const polynom& other);
    };

}
