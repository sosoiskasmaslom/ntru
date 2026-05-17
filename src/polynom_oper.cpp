
#include <iostream>
#include "polynom.h"
using namespace own;


template<typename F>
void edit_v(own::size_t *v, unsigned N, F op) {
    for(own::size_t *end = v+N; v<end; op(v++)) {}
}


polynom& polynom::operator=(const polynom& other) {
    if (this == &other)
    { return *this; }

    delete[] _vector;

    _N = other.get_N();
    _vector = new size_t[_N];
    for(
        size_t *t=_vector, *o=other.get_v();
        t < _vector+_N;
        *(t++) = *(o++)
    ) {}

    return *this;
}


polynom& polynom::operator+=(size_t x) {
    *_vector += x;
    return *this;
}

polynom& polynom::operator-=(size_t x)
{ return *this+=(-1*x); }

polynom& polynom::operator*=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v *= x; });
    return *this;
}

polynom& polynom::operator/=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v /= x; });
    return *this;
}

polynom& polynom::operator%=(size_t x) {
    edit_v(_vector, _N, [&x](size_t *v){ *v %= x; });
    return *this;
}


polynom& polynom::operator+=(polynom other) {
    for(
        size_t *t=_vector, *o=other.get_v();
        t < _vector+min(_N, other.get_N());
        *(t++) += *(o++)
       ) {}
    return *this;
}

polynom& polynom::operator-=(polynom other)
{ return *this += other *= -1; }


polynom polynom::operator+(polynom other)
{ return other += *this; }

polynom polynom::operator-(polynom other)
{ return other -= *this; }


polynom polynom::operator*(polynom other) {
    if (this->_N != other.get_N())
    { return *this; }

    polynom tmp {_N, 0};
    for(unsigned k=0; k<_N; ++k) {
        for(unsigned i=0; i<k+1; ++i)
        { tmp[k] += this->at(i) * other.at(k-i); }

        for(unsigned i=k+1; i<_N; ++i)
        { tmp[k] += this->at(i) * other.at(_N+k-i); }
    }

    return tmp;
}


polynom polynom::operator/(polynom other) {
    int deg_a = this->get_d();
    int deg_b = other.get_d();

    //std::cerr << "deg_a=" << deg_a << " deg_b=" << deg_b << "\n";
    //std::cerr << "this->_N=" << get_N() << " other._N=" << other.get_N() << "\n";

    if (deg_b <= 0)
        throw std::invalid_argument("Division by zero polynomial");

    // Если степень делимого меньше степени делителя — частное равно нулю
    if (deg_a < deg_b)
        return polynom(); // нулевой полином (конструктор по умолчанию)

    unsigned quot_deg = (unsigned)(deg_a - deg_b);

    // Работаем с копией делимого
    polynom remainder(*this);
    polynom quotient(quot_deg+1); // массив коэффициентов частного
    for (unsigned i = 0; i <= quot_deg; ++i)
        quotient[i] = 0;

    // Ведущий коэффициент делителя
    size_t lead_b = other[deg_b];

    for (int i = deg_a - deg_b; i >= 0; --i) {
        // Текущая степень остатка, с которой работаем
        int cur_deg = i + deg_b;

        // Коэффициент очередного члена частного
        if (lead_b == 0)
            throw std::runtime_error(
                "Leading coefficient is zero — check degree()"
            );
        size_t coef = remainder[cur_deg] / lead_b;
        quotient[i] = coef;

        // Вычитаем из остатка: remainder -= coef * x^i * other
        for (int j = 0; j <= deg_b; ++j)
            remainder[i + j] -= coef * other[j];
    }

    return quotient;
}

polynom polynom::operator%(polynom other) {
    int deg_a = this->get_d();
    int deg_b = other.get_d();

    if (deg_b < 0)
        throw std::invalid_argument("Division by zero polynomial");

    // Если степень делимого меньше — остаток равен самому делимому
    if (deg_a < deg_b)
        return polynom(*this);

    polynom remainder(*this);
    size_t lead_b = other[deg_b];

    for (int i = deg_a - deg_b; i >= 0; --i) {
        int cur_deg = i + deg_b;

        size_t coef = remainder[cur_deg] / lead_b;

        for (int j = 0; j <= deg_b; ++j)
            remainder[i + j] -= coef * other[j];
    }

    // Определяем фактическую степень остатка
    int rem_deg = remainder.get_d();
    if (rem_deg < 0)
        return polynom(); // нулевой полином

    polynom result((unsigned)rem_deg);
    for (int i = 0; i <= rem_deg; ++i)
        result[i] = remainder[i];

    return result;
}

own::size_t  polynom::operator[](unsigned i) const
{ return this->at(i); }

own::size_t& polynom::operator[](unsigned i)
{ return this->at(i); }
