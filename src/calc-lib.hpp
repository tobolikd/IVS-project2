/**
 * @file calc-lib.hpp
 * @author Timotej Halenár (xhalen00), David Tobolík (xtobol06)
 * @brief Calculator math library header - IVS Project 2022/23 // VUT FIT
 * @version 0.1
 * @date 2023-03-28
 * 
 * 
 */

#ifndef IVS_MATH_LIB
#define IVS_MATH_LIB

#include <vector>
#include <string>
#include <variant>
#include <algorithm>
#include <iostream>


/**
* @brief Token structure.
* 
*/
typedef struct token
{
    int int_value;
    float float_value;
    int type;
}token_t;

/**
 * @brief Enumeration of token types.
 * 
 */
enum token_types{
    ADD_T,
    MUL_T,
    LBR_T,
    RBR_T,
    ID_T,
    END_T,
    DIV_T,
    SUB_T,
    FAC_T,
    EXP_T,
    SQR_T,
    EXPR_T
};

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

template<typename T>
T power(T x, unsigned int n) {
    T result = 1;
    for (int i = 0; i < n; i++) {
        result *= x;
    }
    return result;
}

double root(double num, double n_);

template<typename T>
double sin(T x) {return 0;}

template<typename T>
double cos(T x) {return 0;}

long long int factorial(unsigned int x);

std::vector<token_t> parseExpression(std::string expression);

int evaluateIntExpression(std::vector<token_t> expression);

float evaluateFloatExpression(std::vector<token_t> expression);

void printToken(token_t token);

void printTokenVector(std::vector<token_t> token_vector);

token_t topTerminal(std::vector<token_t> token_vector);

#endif //IVS_MATH_LIB

//**********End of file calc-lib.hpp************
