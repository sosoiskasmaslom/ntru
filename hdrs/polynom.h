
#pragma once
#include <ostream>

namespace own {

    using size_t = int;

    size_t max(size_t a, size_t b);
    size_t min(size_t a, size_t b);
    size_t abs(size_t a);

    size_t randint(size_t min, size_t max);

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

        polynom& operator+=(const polynom& other);
        polynom& operator-=(const polynom& other);
        polynom& operator*=(const polynom& other);

        polynom operator+(size_t x) const;
        polynom operator-(size_t x) const;
        polynom operator*(size_t x) const;
        polynom operator/(size_t x) const;
        polynom operator%(size_t x) const;

        polynom operator+(const polynom& other) const;
        polynom operator-(const polynom& other) const;
        polynom operator*(const polynom& other) const;

        size_t  operator[](unsigned int i) const;
        size_t& operator[](unsigned int i);

        // клон оператора [] в функциональном виде
        size_t  at(unsigned i) const;
        size_t& at(unsigned i);

        unsigned get_N() const; // возвращает _N
        size_t*  get_v() const; // возвращает ссылку на массив
        int      get_d() const; // возвращает степень полинома
                                // (старший ненулевой элемент)

        //нахождение обратного элемента (полинома)
        polynom rev(const polynom& other, size_t p) const;

        std::ostream& draw(std::ostream& out) const;
    };

}
