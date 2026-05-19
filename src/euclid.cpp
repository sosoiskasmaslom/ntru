
#include <ostream>
#include "euclid.h"
using namespace own;

// Расширенный алгоритм Евклида для нахождения обратного к a по модулю p
// Возвращает x такое что a*x ≡ 1 (mod p)
long long own::mod_inverse(long long a, long long p) {
    a = ((a % p) + p) % p; // нормализуем на случай отрицательного a

    long long mod_poly = p, r = a;
    long long old_x = 0, x = 1;

    while (r != 0) {
        long long q = mod_poly / r;
        long long tmp;

        tmp = r;   r   = mod_poly - q * r;   mod_poly = tmp;
        tmp = x;   x   = old_x - q * x;   old_x = tmp;
    }

    // mod_poly — это gcd(a, p)
    if (mod_poly != 1)
        throw std::runtime_error("No modular inverse: gcd(a, p) != 1");

    return ((old_x % p) + p) % p;
}

// Расширенный алгоритм Евклида для полиномов
// Возвращает обратный к f по модулю (mod_poly, p)
// Бросает исключение если обратного не существует
polynom own::poly_inverse(
        const polynom& f, polynom mod_poly, int p
    ) {

    std::cerr << "poly_inverse: f.get_N()=" << f.get_N()
          << " mod_poly.get_N()=" << mod_poly.get_N()
          << " p=" << p << std::endl;

    // работаем с копиями
    polynom r     = f.mod(mod_poly, p);
    polynom old_s = polynom(mod_poly.get_N() + 1, 0); // 0
    polynom s     = polynom(1, 1);                     // 1
                                                       //
    std::cerr << "poly_inverse: copies created" << std::endl;

    while (true) {
        // проверяем что r не нулевой
        bool r_is_zero = true;
        for (unsigned i = 0; i < r.get_N(); i++)
            if (r[i] != 0) { r_is_zero = false; break; }
        if (r_is_zero) break;

        polynom q   = mod_poly.div_mod(r, p);
        polynom tmp = r;
        r     = (mod_poly - q * r).mod(mod_poly, p);
        mod_poly = tmp;

        std::cerr << "poly_inverse: half-life" << std::endl;

        tmp   = s;
        s     = (old_s - q * s).mod(mod_poly, p);
        old_s = tmp;

        std::cerr << "poly_inverse: half-life 2" << std::endl;
    }

    std::cerr << "poly_inverse: circle is ended" << std::endl;

    // mod_poly должен быть константой (степень 0)
    // проверяем что gcd = константа (обратимая по модулю p)
    for (unsigned i = 1; i < mod_poly.get_N(); i++) {
        if (mod_poly[i] != 0)
            throw std::runtime_error("Inverse does not exist: gcd is not constant");
    }

    if (mod_poly[0] == 0)
        throw std::runtime_error("Inverse does not exist: gcd is zero");

    // нормализуем: делим old_s на mod_poly[0] по модулю p
    long long inv_lead = mod_inverse((long long)mod_poly[0], (long long)p);
    polynom result = old_s;
    for (unsigned i = 0; i < result.get_N(); i++)
        result[i] = (((long long)result[i] * inv_lead) % p);

    return result.mod(mod_poly, p);
}
