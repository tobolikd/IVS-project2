#ifndef IVS_MATH_LIB
#define IVS_MATH_LIB

#include <vector>
#include <string>
#include <variant>

namespace IVSMath {
    template<typename T>
    T add(T x, T y);

    template<typename T>
    T subtract(T x, T y);

    template<typename T>
    T multiply(T x, T y);

    template<typename T>
    T divide(T x, T y);

    template<typename T>
    T power(T x, int n);

    double root(double x, double n);

    template<typename T>
    double sin(T x);

    template<typename T>
    double cos(T x);

    long long int factorial(unsigned int x);

    std::vector<std::variant<int, char, float>> parseExpression(std::string expression);
}
#endif //IVS_MATH_LIB
