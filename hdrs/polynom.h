
#pragma once
#include <ostream>

namespace own {

    using size_t = int;

    size_t max(size_t a, size_t b);
    size_t min(size_t a, size_t b);
    size_t pow(size_t a, size_t b);
    size_t abs(size_t a);

    int randint(int min, int max);

    class polynom {
        size_t *_vector; // коэффициенты полинома
        unsigned _N; // размерность многочлена
                     // (по сути размер массива)
    public:
        polynom();
        polynom(unsigned N); // полином с случайными коэффициентами
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

        // обращение к элементу i
        size_t  at(unsigned i) const;
        size_t& at(unsigned i);

        unsigned get_N() const; // возвращает _N (по сути размер массива)
        size_t*  get_v() const; // возвращает ссылку на массив
        int      get_d() const; // возвращает степень полинома
                                // (старший ненулевой элемент)

        polynom& resize(unsigned n); // задает размер полинома в n символов
                           // (без перемещения коэффициентов)
        polynom& fit(); // убирает нули после старшего члена
        polynom& mod(int p); // приводит все коэффициенты по модулю
        polynom& mod(const polynom& other); // приводит все коэффициенты по модулю

        // я знаю что C-like код
        // вообще будет самой некрасивой частью кода
        // я буду делать грязб
        // он будет возвращать ссылку на массив 2ух объектов
        // (освобождение массива лежит на том кто использует)
        // деления нацело и остатка от деления
        // делим по модулю дабы не было дробей
        // P.S. я доволен этим блоком
        polynom* division(const polynom& other) const;
        polynom mult_x(int p) const; // умножение или деление на х
        polynom mult(const polynom& other) const; // обычное умножение
        //нахождение обратного элемента (полинома)
        polynom rev(const polynom& other, size_t p) const;

        std::ostream& draw(std::ostream& out) const;
    };

}
