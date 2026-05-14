
#pragma once
#include <ostream>

namespace own {

    using size_t = int;

    size_t max(size_t a, size_t b);
    size_t min(size_t a, size_t b);
    size_t abs(size_t a);

    class polynom {
        size_t *_vector; // коэффициенты полинома
        unsigned _N; // степень многочлена
    public:
        polynom();
        polynom(unsigned N); // полином с случайными коэффициентами
        polynom(unsigned N, size_t a);
        polynom(unsigned N, size_t *vector);
        polynom(const polynom& other);

        ~polynom();

        polynom& operator=(const polynom& other);

        // скалярные операции
        polynom& operator+=(size_t x);
        polynom& operator-=(size_t x);
        polynom& operator*=(size_t x);
        polynom& operator/=(size_t x);
        polynom& operator%=(size_t x);

        polynom& operator+=(polynom other);
        polynom& operator-=(polynom other);

        polynom operator+(size_t x);
        polynom operator-(size_t x);

        // особые умножение и деление
        // надо будет их описать
        polynom operator*(size_t x);
        polynom operator/(size_t x);
        polynom operator%(size_t x);

        polynom operator+(polynom other);
        polynom operator-(polynom other);
        polynom operator*(polynom other);
        polynom operator/(polynom other);
        polynom operator%(polynom other);

        size_t  operator[](unsigned int i) const;
        size_t& operator[](unsigned int i);

        // клон оператора [] в функциональном виде
        size_t  at(unsigned i) const;
        size_t& at(unsigned i);

        unsigned get_N() const; // возвращает _N
        size_t* get_v() const; // возвращает ссылку на массив

        polynom mult_x(int p) const; // домножаем на степень

        polynom mod(int x) const; // приведение по скалярному модулю
        polynom mod(const polynom& other) const; // приведение по векторному модулю

        std::ostream& draw(std::ostream& out) const;
    };

}
