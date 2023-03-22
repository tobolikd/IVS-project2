#include <stdexcept>
#include <string>
#include <variant>
#include <vector>

#include "calc-lib.hpp"

using namespace std;

template<typename T>
T add(T x, T y) {
    return x + y;
}

template<typename T>
T subtract(T x, T y) {
    return x - y;
}

template<typename T>
T multiply(T x, T y) {
    return x * y;
}

template<typename T>
T divide(T x, T y) {
    if (y == 0)
        throw std::runtime_error("Division by zero");
    return x / y;
}

std::vector<std::variant<int, char, float>> parseExpression(std::string expression) {
    std::vector<std::variant<int, char, float>> parsed;
    return parsed;
    //TODO
}
